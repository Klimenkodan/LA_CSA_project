#include <emmintrin.h>
#include "simd_matrix.h"
#include <iostream>
#include <immintrin.h>
#include <emmintrin.h>
#include <tmmintrin.h>
#include <vector>
#include <new>
#include <type_traits>
#include <cstdint>
#include <atomic>
#include <chrono>
#include <random>

simd_matrix::simd_matrix(size_t r, size_t c) : rows_num(r), cols_num(c) {
	mem_block_size = rows_num * cols_num;
	if ((rows_num*cols_num) % element_align != 0) {
		mem_block_size += element_align - (rows_num *cols_num) % element_align;
	}
	data = new(cache_line_align, std::nothrow) double[mem_block_size];
	for (size_t i = 0; i < mem_block_size; i++) {
		data[i] = 0.0;
	}
}

void simd_matrix::set_data(const double* data_m) {
	for (size_t i = 0; i < mem_block_size; i++) {
		data[i] = data_m[i];
	}
}

void simd_matrix::display() {
	for (size_t i = 0; i < rows_num; i++) {
		for (size_t j = 0; j < cols_num; ++j) {
			std::cout << get_element(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool simd_matrix::equal(const simd_matrix& m, double err) const{
	if (rows_num != m.rows_num || cols_num != m.cols_num)
		return false;
	for (size_t i = 0; i < mem_block_size; ++i) {
		if (std::abs(data[i] - m.data[i])/ data[i] >= err) {
			std::cout << data[i] << " " << m.data[i] << " " << i << std::endl;
			return false;
		}
	}
	return true;
}

void simd_matrix::naive_swap(size_t row1, size_t row2) {
	double inter;
	for (size_t i = 0; i < cols_num; ++i) {
		inter = data[row1 * cols_num + i];
		data[row1 * cols_num + i] = data[row2 * cols_num + i];
		data[row2 * cols_num + i] = inter;
	}
}


void simd_matrix::interchange_rows(size_t row1, size_t row2) {
	for (size_t i = 0; i < cols_num; i++) {
		std::swap(data[row1 * cols_num + i], data[row2 * cols_num + i]);
	}
}

simd_matrix simd_matrix::copy() {
	auto matrix = simd_matrix(rows_num, cols_num);
	matrix.set_data(data);
	return matrix;
}

void simd_matrix::set_element(size_t row, size_t col, double element) {
	data[row * cols_num + col] = element;
}

double simd_matrix::get_element(size_t row, size_t col) const{
	return data[row * cols_num + col];
}

simd_matrix simd_matrix::real_transpose() const{
	auto m1 = simd_matrix(cols_num, rows_num);
	for (size_t i = 0; i < rows_num; i++) {
		for (size_t j = 0; j < cols_num; ++j) {
			m1.set_element(j, i, get_element(i, j));
		}
	}
	return m1;
}

simd_matrix simd_matrix::multiply(simd_matrix& m1) const{
	auto m2 = simd_matrix(rows_num, m1.cols_num);
	double res = 0;
	for (size_t i = 0; i < rows_num; i++) {
		for (size_t k = 0; k < m1.cols_num; k++) {

			for (size_t j = 0; j < cols_num; j++) {
				res += get_element(i, j) * m1.get_element(j, k);
			}
			m2.set_element(i, k, res);
			res = 0;
		}
	}
	return m2;
}

simd_matrix simd_matrix::multiply_sse(const simd_matrix& m1) const{

	auto m2 = simd_matrix(rows_num, m1.cols_num);
	auto m3 = m1.real_transpose();
	__m128d vsum = _mm_set1_pd(0.0);
	for (size_t i = 0; i < rows_num; i++) {
		for (size_t k = 0; k < m3.rows_num; k++) {

			for (size_t j = 0; j < cols_num; j+=2) {
				__m128d v0 =  _mm_loadu_pd(data + i * cols_num + j);
				__m128d v1 = _mm_loadu_pd(m3.data + k * m3.cols_num + j);

				if (cols_num - j < 2) {
					v0[1] = 0.0;
					v1[1] = 0.0;
				}

				v0 = _mm_mul_pd(v0, v1);

				vsum = _mm_add_pd(vsum, v0);
			}
			vsum = _mm_hadd_pd(vsum, vsum);
			double res = _mm_cvtsd_f64(vsum);
			m2.set_element(i, k, res);
			vsum = _mm_set1_pd(0.0);
		}
	}

	return m2;
}

double simd_matrix::dot_product(const simd_matrix& m1) const {
	double res = 0;
	for (size_t i = 0; i < mem_block_size; i++) {
		res += data[i] * m1.data[i];
	}
	return res;

}

double simd_matrix::dot_product_sse(const simd_matrix& m1) const {
	__m128d vsum0 = _mm_setzero_pd();
	for (size_t i = 0; i < mem_block_size; i+=2) {
		__m128d v0 = _mm_loadu_pd(data + i);
		__m128d v1 = _mm_loadu_pd(m1.data + i);

		if (mem_block_size - i < 2) {
			v0[1] = 0;
			v1[1] = 0;
		}

		v0 = _mm_mul_pd(v0, v1);



		vsum0 = _mm_add_pd(vsum0, v0);


	}
	vsum0 = _mm_hadd_pd(vsum0, vsum0);
	double res = _mm_cvtsd_f64(vsum0);
	return res;
}

double simd_matrix::dot_product_sse_unroll(const simd_matrix& m1) const {
	__m128d vsum0 = _mm_setzero_pd();
	__m128d vsum1 = _mm_setzero_pd();
	for (size_t i = 0; i < rows_num * cols_num - rows_num * cols_num % 4; i+=4) {
		__m128d v0 = _mm_loadu_pd(data + i);
		__m128d v1 = _mm_loadu_pd(m1.data + i);

		v0 = _mm_mul_pd(v0, v1);

		__m128d v2 = _mm_loadu_pd(data + i + 2);
		__m128d v3 = _mm_loadu_pd(m1.data + i + 2);


		v2 = _mm_mul_pd(v2, v3);

		vsum0 = _mm_add_pd(vsum0, v0);
		vsum1 = _mm_add_pd(vsum1, v2);


	}
	vsum0 = _mm_add_pd(vsum0, vsum1);
	vsum0 = _mm_hadd_pd(vsum0, vsum0);
	double res = _mm_cvtsd_f64(vsum0);
	int piece = static_cast<int>(rows_num * cols_num) % 4;
	if (piece != 0) {
		for (int i = 0; i < piece; i++) {
			res += data[rows_num * cols_num - 1 - i] * m1.data[rows_num * cols_num - 1 - i];
		}
	}
	return res;
}

double simd_matrix::trace() const{
	double res = 0;
	for (size_t i = 0; i < rows_num; i++) {
		res += get_element(i, i);
	}
	return res;
}

double simd_matrix::trace_sse() const{
	__m128d vsum = _mm_setzero_pd();
	for (size_t i = 0; i < rows_num - rows_num % 2; i+=2) {
		__m128d v0 = {get_element(i, i), get_element(i+1, i+1)};
		vsum = _mm_add_pd(vsum, v0);
	}
	vsum = _mm_hadd_pd(vsum, vsum);
	double res = _mm_cvtsd_f64(vsum);
	if (rows_num % 2 != 0) {
		res += data[cols_num * cols_num -1];
	}
	return res;
}

double simd_matrix::trace_avx_unroll() const{
	__m256d vsum0 = _mm256_set1_pd(0.0);
	__m256d vsum1 = _mm256_set1_pd(0.0);

	for (size_t i = 0; i < rows_num; i+=8) {

		__m256d v0 = {get_element(i, i), get_element(i+1, i+1), get_element(i+2, i+2), get_element(i+3, i+3)};
		__m256d v1 = {get_element(i+4, i+4), get_element(i+5, i+5), get_element(i+6, i+6), get_element(i+7, i+7)};

		vsum0 = _mm256_add_pd(vsum0, v0);
		vsum1 = _mm256_add_pd(vsum1, v1);

	}

	vsum0 = _mm256_add_pd(vsum0, vsum1);
	vsum0 = _mm256_hadd_pd(vsum0, vsum0);

	__m128d sum_high = _mm256_extractf128_pd(vsum0, 1);
	__m128d result = _mm_add_pd(sum_high, _mm256_castpd256_pd128(vsum0));


	double res = _mm_cvtsd_f64(result);
	return res;

}

simd_matrix simd_matrix::add_matrix(const simd_matrix& m, double a_coef, double b_coef) {
	auto m1 = simd_matrix(rows_num, cols_num);
	for (size_t i = 0; i < mem_block_size; i++) {
		m1.data[i] = data[i] * a_coef + m.data[i] * b_coef;
	}
	return m1;
}

simd_matrix simd_matrix::add_matrix_avx(const simd_matrix& m, double a_coef, double b_coef) {
	auto m1 = simd_matrix(rows_num, cols_num);
	const __m256d coef_vec1 = _mm256_set1_pd(a_coef);
	const __m256d coef_vec2 = _mm256_set1_pd(b_coef);
	for (size_t i = 0; i < mem_block_size - mem_block_size % 4; i+=4) {
		__m256d v0 = _mm256_load_pd(data + i);
		__m256d v1 = _mm256_load_pd(m.data + i);

		v0 = _mm256_mul_pd(v0, coef_vec1);

		v1 = _mm256_mul_pd(v1, coef_vec2);

		v0 = _mm256_add_pd(v0, v1);


		m1.data[i] = v0[0];
		m1.data[i+1] = v0[1];


		m1.data[i+2] = v0[2];
		m1.data[i+3] = v0[3];

	}

	if (mem_block_size % 4 != 0) {
		for (int i = 0; i < static_cast<int>(mem_block_size - mem_block_size % 4); i++) {
			size_t ind = rows_num * cols_num - 1 - i;
			m1.data[ind] = data[ind] * a_coef + b_coef * m.data[ind];
		}
	}
	return m1;
}

void simd_matrix::add_to_row_avx(size_t line_to_add_to, size_t line_to_add, double coef) {
	const __m256d coeff = _mm256_set1_pd(coef);
	for (size_t i =0; i < cols_num - cols_num % 4; i+=4) {
		__m256d v1 = _mm256_loadu_pd(data + line_to_add_to * cols_num + i);
		__m256d v2 = _mm256_loadu_pd(data + line_to_add * cols_num + i);
		v2 = _mm256_mul_pd(v2, coeff);


		v1 = _mm256_add_pd(v1, v2);

		for (int j = 0; j < 4; j++) {
			set_element(line_to_add_to, i+j, v1[j]);
		}
	}
	for (int i = 0; i < static_cast<int>(cols_num % 4); i++) {
		set_element(line_to_add_to, cols_num - i - 1, get_element(line_to_add, cols_num - i - 1) * coef + get_element(line_to_add_to, cols_num - i - 1));
	}
}

void simd_matrix::add_to_row(size_t line_to_add_to, size_t line_to_add, double coef) {
	for (size_t i =0; i < cols_num; i++) {
		set_element(line_to_add_to, i, get_element(line_to_add, i) * coef + get_element(line_to_add_to, i));
	}
}


simd_matrix simd_matrix::row_echelon_avx(){
	int cur_line = 0;
	double coef;
	simd_matrix matrix = copy();
	for (size_t i = 0; i < cols_num; i++) {
		for (size_t j = cur_line; j < rows_num; j++) {
			if (matrix.get_element(j, i) != 0) {
				if (j != i) {

					matrix.interchange_rows(j, j - cur_line - 1);
				}

				for (size_t k = cur_line + 1; k < rows_num; k++) {
					coef = -1 * (matrix.get_element(k, cur_line) / matrix.get_element(cur_line, cur_line));
					if (coef != 0)
						matrix.add_to_row_avx(k, cur_line, coef);

				}
				cur_line++;
				break;
			}
		}
	}
	return matrix;
}

