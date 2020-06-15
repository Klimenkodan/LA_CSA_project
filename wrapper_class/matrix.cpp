#include <string>
#include "../headers/matrix.h"
#include "../helper_functions/helper_functions.h"
#include <iostream>
#include <cassert>
#include <array>
#include "../headers/vector_operations.h"

double* Matrix::get_cell_ref(int row_num, int col_num) {
	int idx = col_num + get_width() * row_num;

	return &matrix[idx];
}

Matrix::Matrix(int m, int n) {
	assert(m > 0 && n > 0);
	matrix = new double[m * n]{0};
	width = n;
	height = m;
}

Matrix::Matrix(int m, int n, const std::vector<double>& values) {
	assert(m > 0 && n > 0 && values.size() == m * n);
	matrix = new double[m * n];
	width = n;
	height = m;
	for (int i = 0; i < m * n; ++i) {
		matrix[i] = values[i];
	}
}

double Matrix::get_element(int row_num, int col_num) const{
	assert(check_valid(row_num, col_num, get_width(), get_height()));
	return matrix[col_num + get_width() * row_num];
}

void Matrix::set_element(int row_num, int col_num, double el) {
	assert(check_valid(row_num, col_num, get_width(), get_height()));
	matrix[col_num + row_num * get_width()] = el;
}

void Matrix::scalar_multiply(double scalar) {
	for (int i=0; i < get_height(); i++) {
		for (int j = 0; j < get_width(); j++) {
			set_element(i, j, get_element(i, j) * scalar);
		}
	}
}

Matrix* Matrix::copy_column(int col_num) {
	assert(col_num >= 0 && col_num < get_width());
	auto column = new Matrix(get_height(), 1);
	for (int i = 0; i < get_height(); i++) {
		column->set_element(i, 0, get_element(i, col_num));
	}
	return column;

}
std::string Matrix::representation() {
	std::string repr;
	for (int i=0; i < get_height(); i++) {
		repr += "| ";
		for (int j=0; j < get_width(); j++) {
			std::string num_repr = number_repr(get_element(i, j));
			repr += num_repr + " ";
		}
		repr += "|\n";
	}
	return repr;
}

Matrix *Matrix::copy() {
	auto* new_matrix = new Matrix(get_height(), get_width());
	for (int i = 0; i < get_height(); i++) {
		for (int j = 0; j < get_width(); j++) {
			new_matrix->set_element(i, j, get_element(i, j));
		}
	}
	return new_matrix;
}

bool Matrix::equal(Matrix* b, double err) {
	assert(get_height() == b->get_height() && get_width() == b->get_width());
	for (int i = 0; i < get_height(); i++) {
		for (int j = 0; j < get_width(); j++) {
			if (std::abs((get_element(i, j) - b->get_element(i, j) )) > err) {
				return false;
			}
		}
	}
	return true;
}

void Matrix::add_column(Matrix* column, int num_column) {
	assert(num_column >= 0 || num_column < get_width() || is_vector(column) || get_height() == column->get_height());
	for (int i = 0; i < get_height(); i++) {
		set_element(i, num_column, column->get_element(i, 0));
	}

}

void Matrix::interchange_rows(int row_1, int row_2) {
	assert(0 <= row_1 && row_1 < get_height() && 0 <= row_2 && row_2 < get_height());
	if (row_1 == row_2)
		return;
	Matrix* row = copy_row(row_1);
	for (int i = 0; i < get_width(); ++i) {
		set_element(row_1, i, get_element(row_2, i));
	}

	for (int i = 0; i < get_width(); i++) {
		set_element(row_2, i, row->get_element(0, i));
	}
}

Matrix* Matrix::copy_row(int row_num) {
	auto* row = new Matrix(1, get_width());
	for (int i = 0; i < get_width(); i++) {
		row->set_element(0, i, get_element(row_num, i));
	}
	return row;
}

void Matrix::add_to_row(int row_to, int row_that, double coeff) {
	assert(0 <= row_to && row_to < get_height() && 0 <= row_that && row_that < get_height());
	if (row_to == row_that)
		multiply_row(row_to, coeff + 1);
	for (int i = 0; i < get_width(); ++i) {
		set_element(row_to, i, get_element(row_to, i) + (coeff * get_element(row_that, i)));
	}
}

void Matrix::multiply_row(int row, double coeff) {
	assert(0 <= row && row < get_height());
	for (int i = 0; i < get_width(); ++i) {
		set_element(row, i, get_element(row, i) * coeff);
	}
}
