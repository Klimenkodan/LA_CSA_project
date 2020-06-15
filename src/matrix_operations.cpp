#include <vector>
#include <cmath>
#include <map>
#include <cassert>
#include "../headers/matrix_operations.h"
#include "../headers/vector_operations.h"

bool sizes_equal(Matrix* a, Matrix* b) {
	return (b->get_width() == a->get_width() && b->get_height() == a->get_height());
}

bool sizes_eq(const Matrix& a, const Matrix& b) {
	return (b.get_width() == a.get_width() && b.get_height() == a.get_height());
}

Matrix* add_matrix(Matrix* a, Matrix* b, double a_coef, double b_coef) {
	assert(sizes_equal(a, b));
	auto* c = new Matrix(a->get_height(), a->get_width());
	for (int i = 0; i < a->get_height(); i++) {
		for (int j = 0; j < a->get_width(); ++j) {
			c->set_element(i, j, (a->get_element(i, j) * a_coef) + (b->get_element(i, j) * b_coef));
		}
	}
	return c;
}


Matrix* multiply_matrix(Matrix* a , Matrix* b) {
	if (a->get_width() != b->get_height()) {
		std::cout << "matrices can not be multiplied" << std::endl;
		return nullptr;
	}

	auto* c = new Matrix(a->get_height(), b->get_width());
	double vector_mult = 0;

	for (int i = 0; i < a->get_height(); i++) {
		for (int j = 0; j < b->get_width(); j++) {
			for (int k = 0; k < a->get_width(); k++) {
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
	auto b = new Matrix(a->get_height(), a->get_width());
	for (int i =0; i < a->get_height(); i++) {
		for (int j =0; j < a->get_width(); j++) {
			b->set_element(i, j, a->get_element(i, j) * mul);
		}

	}
	return b;
}



Matrix* row_echelon(Matrix* matrix) {
	using std::cout;
	using std::endl;
	int cur_line = 0;
	double coef;
	for (int i = 0; i < matrix->get_width(); i++) {
		for (int j = cur_line; j < matrix->get_height(); j++) {
			if (matrix->get_element(j, i) != 0) {
					for (int k = 0; k < j - cur_line; ++k) {
						matrix->interchange_rows(j - k, j - k - 1);
					}

				for (int k = cur_line + 1; k < matrix->get_height(); k++) {
					coef = -1 * (matrix->get_element(k, i) / matrix->get_element(cur_line, i));
					if (coef != 0)
						matrix->add_to_row(k, cur_line, coef);

				}
				cur_line++;
				break;
			}
		}
		}
	return matrix;
}

Matrix* rref(Matrix* matrix) {
	matrix = row_echelon(matrix);
	double coef;
	for (int i = 0; i < matrix->get_height(); i++) {
		for (int j = i; j < matrix->get_width(); j++) {
			if (matrix->get_element(i, j) != 0) {
				matrix->multiply_row(i, 1 / matrix->get_element(i, j));
				for (int k = 0; k < i; k++) {
					coef = -1 * (matrix->get_element(k, j) /matrix->get_element(i, j));
					if (coef != 0)
						matrix->add_to_row(k, i, coef);
				}
				break;
			}
		}
	}
	return matrix;
}

Matrix* inv(Matrix* matrix1) {
	assert(matrix1->get_width() == matrix1->get_height());
	Matrix* matrix = matrix1->copy();
	Matrix* ident = identity(matrix->get_width());

	int cur_line = 0;
	double coef;

	for (int i = 0; i < matrix->get_width(); i++) {
		for (int j = cur_line; j < matrix->get_height(); j++) {
			if (matrix->get_element(j, i) != 0) {
				if (i != j) {
					std::cout << "swap  " << j << cur_line << std::endl;
					ident->interchange_rows(j, cur_line);
					matrix->interchange_rows(j, cur_line);
				}
				coef = 1/matrix->get_element(cur_line, i);
				matrix->multiply_row(cur_line, coef);
				ident->multiply_row(cur_line, coef);

				for (int k = 0; k < cur_line; k++) {
					coef = -1 * (matrix->get_element(k, i) / matrix->get_element(cur_line, i));
					if (coef != 0) {
						matrix->add_to_row(k, cur_line, coef);
						ident->add_to_row(k, cur_line, coef);
					}
				}

				for (int k = cur_line + 1; k < matrix->get_height(); k++) {
					coef = -1 * (matrix->get_element(k, i) / matrix->get_element(cur_line, i));
					if (coef != 0) {
						matrix->add_to_row(k, cur_line, coef);
						ident->add_to_row(k, cur_line, coef);
					}
				}



				std::cout <<matrix->representation() << std::endl << ident->representation() <<std::endl;
				cur_line++;
				break;
			}
		}
	}
////	return matrix;
	if (!matrix->equal(identity(matrix->get_height()), 0.00005)) {
		std::cout << "the matrix is not invertible" << std::endl;
		return nullptr;
	}
	std::cout << matrix->representation();
	return ident;

}



int rank(Matrix * a) {
	Matrix* ref = row_echelon(a);
	int rank = a->get_height();
	bool empty = true;
	for (int i = a->get_height() -1; i >= 0; i--) {
		for (int j = 0; j < a->get_width(); j++) {
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
	auto* res = new Matrix(m->get_width(), m->get_height());
	for (int i = 0; i < m->get_height(); i++) {
		for (int j = 0; j < m->get_width(); j++) {
			res->set_element(j,i, m->get_element(i, j));
		}
	}

	return res;
}

bool check_square(Matrix* matrix){
	return matrix->get_width() == matrix->get_height();
}

double determinant(Matrix* matrix){
	if ( !check_square(matrix) ){
		std::cout << "Non-square matrices have no determinants ";
		return -1;
	}
	matrix = row_echelon(matrix);
	double det = 1;
	for (int i = 0; i < matrix->get_height(); i++){
		det *= matrix->get_element(i, i);
	}
	return det;
}

double trace(Matrix* matrix) {
	if ( !check_square(matrix) ){
		std::cout << "Non-square matrices don't have a trace ";
		return -1;
	}
	double trace = 0;
	for (int i = 0; i < matrix->get_height(); i++) {
		trace += matrix->get_element(i, i);
	}

	return trace;
}


double gram_coef(Matrix* a, Matrix* b) {
	return dot_product(a, b) / dot_product(b, b);
}

bool is_upper(Matrix* matrix) {
	if (!check_square(matrix)) {
		return false;
	}
	for (int i = 1; i < matrix->get_height(); i++) {
		for (int j = 0; j < i; ++j) {
			//todo:choose method of terminating the loop(precision or number iterations)
			if (std::abs(matrix->get_element(i, j)) > 0.0000005) {
				return false;
			}
		}
	}
	return true;
}


std::map<std::string, Matrix*> QR_factorization(Matrix* matrix) {
	using std::cout;
	std::map<std::string, Matrix*> qr;
	auto* Q = new Matrix(matrix->get_height(), matrix->get_width());
	auto* R = new Matrix(matrix->get_width(), matrix->get_width());
	Matrix* cur;
	Matrix* res;
	Matrix* interm;
	double _norm;
	cur = matrix->copy_column(0);
	_norm = norm(cur);
	cur->scalar_multiply(1 / _norm);
	for (int i = 0; i < cur->get_height(); i++) {
		Q->set_element(i, 0, cur->get_element(i, 0));
	}
	//todo: Computing R is not optimized
	for (int i = 0; i < matrix->get_width(); ++i) {
		interm = matrix->copy_column(i);
		R->set_element(0, i, dot_product(cur, interm));
	}


	for (int i = 1; i < matrix->get_width(); i++) {
		cur = matrix->copy_column(i);

		res = cur->copy();

		for (int k = 0; k < i; k++) {
			interm = Q->copy_column(k);
			interm->scalar_multiply(gram_coef(cur, interm));
			res = add_matrix(res, interm, 1, -1);
		}

		for (int p = 0; p < matrix->get_height(); p++) {
			_norm = norm(res);
			res->scalar_multiply(1 / _norm);
			Q->set_element(p, i, res->get_element(p, 0));
		}
		R->set_element(i, i, dot_product(cur, res));
		for (int p = i + 1; p < matrix->get_width(); p++) {
			interm = matrix->copy_column(p);
			R->set_element(i, p, dot_product(res, interm));
		}
	}


	qr["Q"] = Q;
	qr["R"] = R;
	return qr;
}

std::vector<double> qr_method_eigenvalues(Matrix* matrix) {
	std::vector<double> eigenvalues;
	int max_iter = 100;
	int k = 0;
	std::map<std::string, Matrix*> qr;
	while (!is_upper(matrix) || k != max_iter) {
		qr = QR_factorization(matrix);

		matrix = multiply_matrix(qr["R"], qr["Q"]);
		k++;
	}

	for (int i = 0; i < matrix->get_width(); i++) {
		eigenvalues.emplace_back(matrix->get_element(i, i));
	}

	return eigenvalues;

}
