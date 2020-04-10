#include <iostream>
#include "../headers/vector_operations.h"
#include "../headers/matrix_operations.h"
#include <map>
#include "../headers/matrix.h"

bool is_vector( Matrix* a) {
	return a->height == 1 || a->width == 1;
}

double dot_product(std::vector<double>* a, std::vector<double>* b) {
	if (a->size() != b->size()) {
		std::cout << "vectors sizes aren't equal" << std::endl;
		return -1;
	}
	double vector_mult = 0;
	for (size_t i = 0; i < a->size(); i++) {
		vector_mult += a->at(i) * b->at(i);
	}

	return vector_mult;
}

double dot_product(Matrix* a, Matrix* b) {
	if (a->width != b->width || a->height != b->height || !is_vector(a) || !is_vector(b)) {
		std::cout << "vectors sizes aren't equal" << std::endl;
		return -1;
	}
	double vector_mult = 0;

	if (a->height == 1) {
		for (size_t i = 0; i < a->width; i++) {
			vector_mult += a->get_element(i, 0) * b->get_element(i, 0);
		}
	}

	else {
		for (size_t i = 0; i < a->height; i++) {
			vector_mult += a->get_element(0, i) * b->get_element(0, i);
		}
	}

	return vector_mult;
}

bool orthogonal(Matrix*a , Matrix* b) {
	return dot_product(a, b) == 0;
}

bool orthogonal(std::vector<double>* a,  std::vector<double>* b) {
	return dot_product(a, b) == 0;
}

bool collinear(Matrix*a , Matrix* b) {
	if (a->width != b->width || a->height != b->height || !is_vector(a) || !is_vector(b)) {
		std::cout << "vectors sizes aren't equal" << std::endl;
		return -1;
	}
	double coeff = a->get_element(0, 0) / b->get_element(0, 0);


	if (a->height == 1) {
		for (int i = 1; i < a->width; i++) {
			if (coeff != a->get_element(i, 0) / b->get_element(i, 0)) {
				return false;
			}
		}
		return true;
	}

	for (int i = 1; i < a->height; i++) {
		if (coeff != a->get_element(0, i) / b->get_element(0, i)) {
			return false;
		}
	}
	return true;
}

bool collinear(std::vector<double>* a,  std::vector<double>* b) {
	double coeff = a->at(0) / b->at(0);
	for (size_t i = 1; i < a->size(); i++) {
		if (coeff != a->at(i) / b->at(i)) {
			return false;
		}
	}
	return true;
}