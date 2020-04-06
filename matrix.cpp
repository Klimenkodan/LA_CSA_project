#include <string>
#include "matrix.h"
#include "helper_functions.h"
#include <iostream>

double Matrix::get_element(int row_num, int col_num) {
	return matrix[col_num + weight * row_num];
}

void Matrix::set_element(int row_num, int col_num, double el) {

	matrix[col_num + row_num * weight] = el;
}

void Matrix::scalar_multiply(double scalar) {
	for (int i=0; i < height; i++) {
		for (int j = 0; j < weight; j++) {
			matrix[j + i * weight] *= scalar;
		}
	}
}

std::string Matrix::representation() {
	std::string repr;
	for (int i=0; i < height; i++) {
		repr += "| ";
		for (int j=0; j < weight; j++) {
			std::string num_repr = number_repr(get_element(i, j));
			repr += num_repr + " ";
		}
		repr += "|\n";
	}
	return repr;
}


