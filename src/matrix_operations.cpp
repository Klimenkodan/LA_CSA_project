#include <vector>
#include <cmath>
#include "../headers/matrix_operations.h"

double add_or_subtract(double a, double b, bool add) {
	return add ? a + b: a - b;
}


bool sizes_equal(const Matrix* a, const Matrix* b) {
	return (b->width == a->width && b->height == a->height);
}


Matrix* add_subtract(Matrix *a, Matrix *b, bool add) {
	if(!sizes_equal(a, b)) {
		std::cout << "the matrices aren't of equal size" << std::endl;
		return new Matrix(0, 0);
	}
	auto* c = new Matrix(a->height, a->width);

	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < a->width; j++) {
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
	if (a->width != b->height) {
		std::cout << "matrices can not be multiplied" << std::endl;
		return nullptr;
	}

	auto* c = new Matrix(a->height, b->width);
	double vector_mult = 0;

	for (int i = 0; i < a->height; i++) {
		for (int j = 0; j < b->width; j++) {
			for (int k = 0; k < a->width; k++) {
				vector_mult += a->get_element(i, k) * b->get_element(k, j);
			}
			c->set_element(i, j, vector_mult);
			vector_mult = 0;
		}
	}
	return c;
}

Matrix* identity(int num_rows) {
	auto* matrix = new Matrix(num_rows, num_rows);
	for (int i = 0; i < num_rows; i++){
		matrix->set_element(i, i, 1);
	}
	return matrix;
}

Matrix* scalar_multiply(Matrix* a, double mul) {
	auto* b = new Matrix(a->height, a->width);
	for (int i =0; i < a->height; i++) {
		for (int j =0; j < a->height * a->width; j++) {
			b->set_element(i, j, a->get_element(i, j) * mul);
		}

	}
	return b;
}


Matrix* row_echelon(Matrix* a) {
	Matrix* b = a->copy();
	int cur_line = 0;
	double coeff;
	double interm;
	int j = 0;
	for (j = 0; j < a->width; j++) {
		for (int i = cur_line; i < a->height - 1; i++) {
			if (b->get_element(i, j) != 0) {
				if (i != cur_line) {
					for (int k = 0; k < a->width; k++) {
						interm = b->get_element(i, k);
						b->set_element(i, k, b->get_element(cur_line, k));
						b->set_element(cur_line, k, interm);
					}
				}
					for (int p = cur_line + 1; p < a->height; p++) {
						coeff =  b->get_element(p, j) / b->get_element(cur_line, j);
						for (int q = j; q < a->width; q++) {
							b->set_element(p, q, b->get_element(p, q) - (coeff * b->get_element(cur_line, q)));
						}
				}

			cur_line ++;
			break;
			}

		}
	}
	return b;
}

Matrix* inverse(Matrix* a) {
	Matrix* b = a->copy();
	Matrix* ident = identity(a->width);
	int cur_line = 0;
	double div;
	double coeff;
	double interm;
	double interm_id;
	int j = 0;
	for (j = 0; j < a->width; j++) {
		for (int i = cur_line; i < a->height; i++) {
			std::cout << b->representation() << std::endl;
			std::cout << ident->representation() << std::endl;
			if (b->get_element(i, j) != 0) {
				if (i != cur_line) {
					for (int k = 0; k < a->width; k++) {
						interm_id = ident->get_element(i, k);
						ident->set_element(i, k, ident->get_element(cur_line, k));
						ident->set_element(cur_line, k, interm_id);

						interm = b->get_element(i, k);
						b->set_element(i, k, b->get_element(cur_line, k));
						b->set_element(cur_line, k, interm);
					}
				}
				div = b->get_element(cur_line, j);
				for (int p = 0; p < cur_line; p++) {
					coeff =  b->get_element(p, j) / div;
					for (int q = 0; q < a->width; q++) {
						ident->set_element(p, q, ident->get_element(p, q) - (coeff * ident->get_element(cur_line, q)));

						b->set_element(p, q, b->get_element(p, q) - (coeff * b->get_element(cur_line, q)));
					}
				}



				for (int r = cur_line + 1; r < a->height; r++) {
					coeff =  b->get_element(r, j) / div;
					for (int q = 0; q < a->width; q++) {
						ident->set_element(r, q, ident->get_element(r, q) - (coeff * ident->get_element(cur_line, q)));

						b->set_element(r, q, b->get_element(r, q) - (coeff * b->get_element(cur_line, q)));
					}
				}


				for (int q = 0; q < a->width; q++) {
					ident->set_element(cur_line, q, ident->get_element(cur_line, q) / div);
					b->set_element(cur_line, q, b->get_element(cur_line, q) / div);
				}

				cur_line ++;
				break;
			}

		}
	}
	if (!b->equal(identity(b->width))) {
		std::cout << "the matrix is not invertible" << std::endl;
		return nullptr;
	}
	return ident;
}

int rank(Matrix * a) {
	Matrix* ref = row_echelon(a);
	int rank = a->height;
	bool empty = true;
	for (int i = a->height -1; i > 0; i--) {
		for (int j = 0; j < a->width; j++) {
			empty &= (ref->get_element(i, j) == 0);
		}
		if (empty) {
			rank --;
		}
		else {
			return rank;
		}
	}
	return rank;
}

Matrix* solve_equation(Matrix* matrix, Matrix* vector) {
	Matrix* inv = inverse(matrix);
	if (inv == nullptr) {
		return nullptr;
	}

	Matrix* solution = multiply_matrix(inv, vector);
	if (solution == nullptr) {
		return nullptr;
	}

	return solution;
}

Matrix* transpose(Matrix* m) {
	auto* res = new Matrix(m->width, m->height);
	for (int i = 0; i < m->height; i++) {
		for (int j = 0; j < m->width; j++) {
			res->set_element(j,i, m->get_element(i, j));
		}
	}

	return res;
}

bool check_square(Matrix* matrix){
	return matrix->width == matrix->height;
}

double determinant(Matrix* matrix){
	if ( !check_square(matrix) ){
		std::cout << "Non-square matrices have no determinants ";
		return -1;
	}
	matrix = row_echelon(matrix);
	double det = 1;
	for (int i = 0; i < matrix->height; i++){
		det *= matrix->get_element( i, i );
	}
	det = round( det * pow(10,5) ) / pow(10,5);
	return det;
}
