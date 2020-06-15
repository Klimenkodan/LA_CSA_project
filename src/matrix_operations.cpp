#include <vector>
#include <cmath>
#include <map>
#include <cassert>
#include "../headers/matrix_operations.h"
#include "../headers/vector_operations.h"

bool sizes_equal(Matrix* a, Matrix* b) {
	return (b->get_width() == a->get_width() && b->get_height() == a->get_height());
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

	auto* c = new Matrix(a->get_height(), b->get_height());
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
	auto* b = new Matrix(a->get_height(), a->get_width());
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
				if (j != i) {

					for (int k = 0; k < j - cur_line; ++k) {
						matrix->interchange_rows(j - k, j - k - 1);
					}
				}

				for (int k = cur_line + 1; k < matrix->get_height(); k++) {
					coef = -1 * (matrix->get_element(k, cur_line) / matrix->get_element(cur_line, cur_line));
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

Matrix* inv(Matrix* matrix) {
	assert(matrix->get_width() == matrix->get_height());

	Matrix* ident = identity(matrix->get_width());
	int cur_line = 0;
	double coef;

	for (int i = 0; i < matrix->get_width(); i++) {
		for (int j = cur_line; j < matrix->get_height(); j++) {
			if (matrix->get_element(j, i) != 0) {
				if (j != i) {

					for (int k = 0; k < j - cur_line; ++k) {
						matrix->interchange_rows(j - k, j - k - 1);
					}
				}

				for (int k = cur_line + 1; k < matrix->get_height(); k++) {
					coef = -1 * (matrix->get_element(k, cur_line) / matrix->get_element(cur_line, cur_line));
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




Matrix* inverse(Matrix* a) { //todo: fix with changed row_echelon
	Matrix* b = a->copy();
	Matrix* ident = identity(a->get_width());
	int cur_line = 0;
	double div;
	double coeff;
	double interm;
	double interm_id;
	for (int j = 0; j < a->get_width(); j++) {
		for (int i = cur_line; i < a->get_height(); i++) {
//			std::cout << b->representation() << std::endl;
//			std::cout << ident->representation() << std::endl;
			if (b->get_element(i, j) != 0) {
				if (i != cur_line) {
					for (int k = 0; k < a->get_width(); k++) {
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
					for (int q = 0; q < a->get_width(); q++) {
						ident->set_element(p, q, ident->get_element(p, q) - (coeff * ident->get_element(cur_line, q)));

						b->set_element(p, q, b->get_element(p, q) - (coeff * b->get_element(cur_line, q)));
					}
				}



				for (int r = cur_line + 1; r < a->get_height(); r++) {
					coeff =  b->get_element(r, j) / div;
					for (int q = 0; q < a->get_width(); q++) {
						ident->set_element(r, q, ident->get_element(r, q) - (coeff * ident->get_element(cur_line, q)));

						b->set_element(r, q, b->get_element(r, q) - (coeff * b->get_element(cur_line, q)));
					}
				}


				for (int q = 0; q < a->get_width(); q++) {
					ident->set_element(cur_line, q, ident->get_element(cur_line, q) / div);
					b->set_element(cur_line, q, b->get_element(cur_line, q) / div);
				}

				cur_line ++;
				break;
			}

		}
	}
	if (!b->equal(identity(b->get_height()), 0.00005)) {
		std::cout << "the matrix is not invertible" << std::endl;
		return nullptr;
	}
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
	det = det * pow(10,5) / pow(10,5);
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
			if (i == matrix->get_width() - 1) {
//				cout << gram_coef(cur, interm);
//				cout << res->representation() << std::endl << interm->representation() << std::endl;
			}
//			res = subtract_matrix(res, interm);
			res = add_matrix(res, interm, 1, -1);
//			cout << res->representation();
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
	std::map<std::string, Matrix*> qr;
	while (!is_upper(matrix)) {
		qr = QR_factorization(matrix);
		matrix = multiply_matrix(qr["R"], qr["Q"]);
//		std::cout << matrix->representation() << std::endl;
	}

	for (int i = 0; i < matrix->get_width(); i++) {
		eigenvalues.emplace_back(matrix->get_element(i, i));
	}

	return eigenvalues;

}

Matrix* eigen_vectors(Matrix* matrix, const std::vector<double>& eigenvalues) {
	auto* zero_vector = new Matrix(matrix->get_height(), 1);
	Matrix* identity_matr = identity(matrix->get_width());
	auto* result = new Matrix(matrix->get_height(), matrix->get_width());
	Matrix* cur_vector;
	for (int i = 0; i < matrix->get_height(); i++) {
		cur_vector = solve_equation(add_matrix(matrix, identity_matr, 1, eigenvalues[i] * (-1)), zero_vector);
		result->add_column(cur_vector, i);
	}
	return result;
}
