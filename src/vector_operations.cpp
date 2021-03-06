#include <iostream>
#include "../headers/vector_operations.h"
#include "../headers/matrix_operations.h"
#include <map>
#include <cmath>
#include <cassert>
#include "../headers/matrix.h"

bool is_vector( Matrix* a) {
	return a->get_height() == 1 || a->get_width() == 1;
}

double dot_productV(std::vector<double>* a, std::vector<double>* b) {
	if (a->size() != b->size() ) {
		std::cout << "vectors sizes aren't equal" << std::endl;
		return -1;
	}else if ( a->size() == 0 ){
		return -1;
	}
	double vector_mult = 0;
	for (size_t i = 0; i < a->size(); i++) {
		vector_mult += a->at(i) * b->at(i);
	}
	return vector_mult;
}


double dot_product(Matrix* a, Matrix* b) {
	if (!is_vector(a) || !is_vector(b) || a->get_width() * a->get_height() != b->get_width() * b->get_height()) {
		std::cout << "vectors sizes aren't equal" <<  std::endl;
		return -1;
	}
	double vector_mult = 0;

	if (a->get_height() == 1 && b->get_height() == 1) {
//		std::cout << "fuck" << std::endl;
		for (int i = 0; i < a->get_width(); i++) {
			vector_mult += a->get_element(0, i) * b->get_element(0, i);
		}
	}

	else if (a->get_width() == 1 && b->get_width() == 1){
//		std::cout << "this" << std::endl;
		for (int i = 0; i < a->get_height(); i++) {
			vector_mult += a->get_element(i, 0) * b->get_element(i, 0);
		}
	}

	else if (a->get_height() == 1 && b->get_width() == 1) {
//		std::cout << "shit" << std::endl;
		for (int i = 0; i < a->get_width(); i++) {
			vector_mult += a->get_element(0, i) * b->get_element(i, 0);
		}
	}

	else {
//		std::cout << "bruh" << std::endl;
		for (int i = 0; i < a->get_height(); i++) {
			vector_mult += a->get_element(i, 0) * b->get_element(0, i);
		}
	}

	return vector_mult;
}

bool orthogonal(Matrix*a , Matrix* b) {
	return dot_product(a, b) == 0;
}

bool orthogonal(std::vector<double>* a,  std::vector<double>* b) {
	return dot_productV(a, b) == 0;
}

double norm (Matrix* matrix) {
	if (!is_vector(matrix)) {
		throw;
	}
	return sqrt(dot_product(matrix, matrix));
}

bool collinear_m(Matrix*a , Matrix* b) {
	if (a->get_width() != b->get_width() || a->get_height() != b->get_height() || !is_vector(a) || !is_vector(b)) {
		std::cout << "vectors sizes aren't equal" << std::endl;
		return -1;
	}
	double coeff = a->get_element(0, 0) / b->get_element(0, 0);

	if (a->get_height() == 1) {
		for (int i = 1; i < a->get_width(); i++) {
			if (coeff != a->get_element(0, i) / b->get_element(0, i)) {
				return false;
			}
		}
		return true;
	}

	for (int i = 1; i < a->get_height(); i++) {
		if (coeff != a->get_element(i, 0) / b->get_element(i, 0)) {
			return false;
		}
	}
	return true;
}

bool collinear_v(std::vector<double>* a, std::vector<double>* b) {

	if (a->size() != b->size()) {
		std::cout << "Vector sizes are not equal.\n";
		return false;
	} else if (a->size() == 0 || b->size() == 0){
		return -1;
	}

	double coeff = a->at(0) / b->at(0);
	for (size_t i = 1; i < a->size(); i++) {
		if (coeff != a->at(i) / b->at(i)) {
			return false;
		}
	}
	return true;
}


bool is_zero_vector( Matrix* v ){
	assert( is_vector(v) );
	bool is_zero = 1;

	if ( v->get_height() > v->get_width() ){
		for (int i = 0; i < v->get_height(); i++){
			is_zero &= v->get_element(i, 0) == 0;
		}
	} else if (v->get_width() >= v->get_height()){
		for (int i = 0; i < v->get_width(); i++){
			is_zero &= v->get_element(0, i) == 0;
		}
	}

	return is_zero;
}