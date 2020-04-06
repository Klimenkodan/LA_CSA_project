#include "matrix_operations.h"

double add_or_subtract(double a, double b, bool add) {
	return add ? a + b: a - b;
}


bool sizes_equal(const Matrix* a, const Matrix* b) {
	return (b->weight == a->weight && b->height == a->height);
}


Matrix* add_subtract(Matrix *a, Matrix *b, bool add) {
	if(!sizes_equal(a, b)) {
		std::cout << "the matrices aren't of equal size" << std::endl;
		return new Matrix(0, 0);
	}
	auto* c = new Matrix(a->height, a->weight);

	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->weight; j++) {
			std::cout << i << std::endl;
			c->set_element(i, j, add_or_subtract(a->get_element(i, j), b->get_element(i, j), add));
		}
	}
	return c;
}



Matrix* add_matrix(Matrix* a, Matrix* b) {
	return add_subtract(a, b, true);

}

Matrix* subtract_matrix(Matrix* a, Matrix* b) {
	return add_subtract(a, b, false);
}



Matrix* multiply_matrix(Matrix* a , Matrix* b) {
	if (a->weight != b->height) {
		std::cout << "matrices can not be multiplied" << std::endl;
		return nullptr;
	}

	auto* c = new Matrix(a->height, b->weight);
	double vector_mult = 0;

	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < b->weight; j++) {
			for (int k = 0; k < a->weight; k++) {
				vector_mult += a->get_element(i, k) * b->get_element(k, j);
			}
			c->set_element(i, j, vector_mult);
			vector_mult = 0;
		}
	}
	return c;
}
