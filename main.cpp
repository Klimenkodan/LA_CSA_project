#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "matrix.h"
#include "matrix_operations.h"
#include "helper_functions.h"
#include "vector_operations.h"


int main() {
	auto* a = new Matrix(3, 3);
	auto* b = new Matrix(3,  4);
	auto* c = new Matrix(3, 1);
	Matrix* d;
	Matrix* f;
	auto* v_arr = new Matrix*[3];

	auto* v_set1 = new std::vector<Matrix*>;
	a->set_element(0, 0, 1);
	a->set_element(0, 1, 2);
	a->set_element(0, 2, 3);
	a->set_element(1, 0, 65);
	a->set_element(1, 1, 3);
	a->set_element(1, 2, 7);
	a->set_element(2, 0, 12);
	a->set_element(2, 1, 5);
	a->set_element(2, 2, 8);


	std::cout << a->representation() << std::endl;

	b->set_element(0, 0, 12);
	b->set_element(0, 1, 5);
	b->set_element(0, 2, 8);
	b->set_element(0, 3, 8);
	b->set_element(1, 0, 2);
	b->set_element(1, 1, 5);
	b->set_element(1, 2, 1);
	b->set_element(1, 3, 3);
	b->set_element(2, 0, 3);
	b->set_element(2, 1, 0);
	b->set_element(2, 2, 7);
	b->set_element(2, 3, 0);

	c->set_element(0, 0, 1);
	c->set_element(1, 0, 2);
	c->set_element(2, 0, 3);


//	std::cout << b->representation() << std::endl;
//	d = row_echelon(a);
	std::cout << rank(a) << std::endl;
	f = solve_equation(a, c);
	d = inverse(a);
//	d = identity(3);
	std::cout << d->representation() << std::endl;
//	std::vector<Matrix*>* v_set2 = gram_schmidt(v_arr);
	return 0;
}

