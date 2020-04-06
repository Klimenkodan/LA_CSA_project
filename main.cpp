#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "matrix.h"
#include "matrix_operations.h"
#include "helper_functions.h"
#include "vector_operations.h"


int main() {
	Matrix* c;
	auto* a = new Matrix(4, 1);
	auto* b = new Matrix(4,  1);
	for (int i= 0; i < a->height; i++) {
		for(int j= 0; j < a->weight; j++) {
			a->set_element(i, j, 1);
			b->set_element(j, i, 1);
		}
	}
//	c = multiply_matrix(a, b);

	std::cout << a->representation() << std::endl;
	std::cout << b->representation() << std::endl;
//	std::cout << c->representation() << std::endl;
//	c->scalar_multiply(12);
	std::cout << dot_product(a, b) << std::endl;
//	std::cout << c->representation() << std::endl;
	return 0;
}

