//
// Created by dan on 15.06.20.
//

#ifndef SIMD_SIMD_MATRIX_H
#define SIMD_SIMD_MATRIX_H


#include <cstddef>
#include <new>

class simd_matrix {
	static constexpr size_t cache_line_size = 64;
	static constexpr size_t element_align = 8;
	static constexpr std::align_val_t cache_line_align = std::align_val_t(cache_line_size);

	double * data;
	size_t rows_num;
	size_t cols_num;
	size_t mem_block_size;
	public:

		~simd_matrix() {
			delete[] data;
		};

	void set_element(size_t row, size_t col, double element);

	double get_element(size_t row, size_t col) const;

	void set_data(const double* data_m);

	simd_matrix real_transpose() const;

	simd_matrix(size_t r, size_t c);

	simd_matrix multiply(simd_matrix& m1) const;

	simd_matrix multiply_sse(const simd_matrix& m1) const;

	double dot_product(const simd_matrix& m1) const;

	double dot_product_sse(const simd_matrix& m1) const;

	double dot_product_sse_unroll(const simd_matrix& m1) const;

	double trace() const;

	double trace_sse() const;

	double trace_avx_unroll() const;

	simd_matrix add_matrix(const simd_matrix& m, double a_coef, double b_coef);

	simd_matrix add_matrix_avx(const simd_matrix& m, double a_coef, double b_coef);

	simd_matrix copy();

	void display();

	void add_to_row(size_t line_to_add_to, size_t line_to_add, double coef);

	void naive_swap(size_t row1, size_t row2);

	void interchange_rows(size_t row1, size_t row2);

	void add_to_row_avx(size_t line_to_add_to, size_t line_to_add, double coef);

	simd_matrix row_echelon_avx();

	bool equal(const simd_matrix& m, double err) const;



};


#endif //SIMD_SIMD_MATRIX_H
