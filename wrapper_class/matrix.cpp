#include <string>
#include "../headers/matrix.h"
#include "../headers/helper_functions.h"
#include <iostream>

Matrix::Matrix(int m, int n) {
	if (m <= 0 || n <= 0) {
		std::cout<< "matrix can not be of size smaller or equal to zero" << std::endl;
		throw;
	}
	matrix = new double[m * n]{0};
	width = n;
	height = m;
}

double Matrix::get_element(int row_num, int col_num) {
	 if (!check_valid(row_num, col_num, this->width, this->height)) {
	 	std::cout << "there is no such position to get element from"<< std::endl;
	 	return -1;
	 }
	return matrix[col_num + width * row_num];
}

void Matrix::set_element(int row_num, int col_num, double el) {
	if (!check_valid(row_num, col_num, this->width, this->height)) {
		std::cout << "there is no such position to set element"<< std::endl;
		return;
	}
	matrix[col_num + row_num * width] = el;
}

void Matrix::scalar_multiply(double scalar) {
	for (int i=0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			this->set_element(i, j, this->get_element(i, j) * scalar);
		}
	}
}

std::string Matrix::representation() {
	std::string repr;
	for (int i=0; i < height; i++) {
		repr += "| ";
		for (int j=0; j < width; j++) {
			std::string num_repr = number_repr(get_element(i, j));
			repr += num_repr + " ";
		}
		repr += "|\n";
	}
	return repr;
}

Matrix *Matrix::copy() {
	auto* new_matrix = new Matrix(this->height, this->width);
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			new_matrix->set_element(i, j, this->get_element(i, j));
		}
	}
	return new_matrix;
}

bool Matrix::equal(Matrix* b) {
	if (this->height != b->height || this->width != b->width) {
		return false;
	}
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; i < this->height; i++) {
			if (this->get_element(i, j) != b->get_element(i, j)) {
				return false;
			}
		}
	}
	return true;
}

