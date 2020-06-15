#include <vector>
#include <cmath>
#include <map>
#include <cassert>
#include <tgmath.h>
#include "../headers/matrix.h"
#include "../headers/matrix_operations.h"
#include "../headers/vector_operations.h"
#include "../helper_functions/helper_functions.h"

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
    if ( check_square(matrix) && determinant(matrix) != 0 ){
        return identity(matrix->get_height());
    }

    auto matrix_2 = row_echelon(matrix);
    double coef;
    int measure;

    if ( matrix->get_height() > matrix->get_width() ){
        measure = matrix->get_width();
    } else {
        measure = matrix->get_height();
    }

    for (int i = 0; i < measure; i++){
        coef = get_first_nonzero_entry(matrix_2, i) != 0 ? get_first_nonzero_entry(matrix_2, i): 1;
        coef = 1 / coef;
        multiply_matrix_row(matrix_2, i, coef);
    }

    for (int i = 0; i < measure; i++ ){
        for (int j = 0; j < i; j++){
            coef = matrix_2->get_element(j, i);
            matrix_2->add_to_row(j, i, -coef);
        }
    }


	return matrix_2;
}

Matrix* inverse(Matrix* matrix1) {
    assert(matrix1->get_width() == matrix1->get_height());
    assert(determinant(matrix1) != 0);
    Matrix* matrix = matrix1->copy();
    Matrix* ident = identity(matrix->get_width());

    int cur_line = 0;
    double coef, coef_2;


    for(int i = 0; i <  matrix->get_width() ; i++){
        coef = matrix->get_element(i, i);

        for (int j = 0; j < matrix->get_width(); j++){
            matrix->set_element(i, j, matrix->get_element(i,j) / coef );
            ident->set_element(i, j, ident->get_element(i,j) / coef );
        }

        for (int j = 0; j < matrix->get_width(); j++){
            coef_2 = j == i ? 0: matrix->get_element(j, i);
            matrix->add_to_row(j, i, -coef_2);
            ident->add_to_row(j, i, -coef_2);
        }

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
	auto matrix_n = matrix->copy();
	matrix_n = row_echelon(matrix_n);
	double det = 1;
	for (int i = 0; i < matrix_n->get_height(); i++){
		det *= matrix_n->get_element(i, i);
	}
	det = round(det * pow(10,5) ) / pow(10,5);
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

void round_matrix(Matrix* arg){
    for (int i = 0; i < arg->get_height(); i++){
        for (int j = 0; j < arg->get_width(); j++){
            if ( round( arg->get_element(i, j) * 1000 ) == 0 ) {
                arg->set_element( i, j, 0 );
            }
        }
    }
}

std::vector<double> qr_method_eigenvalues(Matrix* matrix) {

	std::vector<double> eigenvalues;
	std::map<std::string, Matrix*> qr;
	int complex_eigenvalues = 0;

    auto m_2 = matrix->copy();
    int shift = 0;

    while ( determinant(m_2) == 0 ){
        m_2 = add_matrix(m_2, identity( m_2->get_width()), 1, 1 );
        shift++;
    }

    if (is_upper(transpose(m_2))){
        m_2 = transpose(m_2);
    }

	while (!is_upper(m_2)) {
		qr = QR_factorization(m_2);
		m_2 = multiply_matrix(qr["R"], qr["Q"]);

        complex_eigenvalues++;
        if (complex_eigenvalues == 500){
            round_matrix(m_2);

            if ( !is_upper( m_2 ) ){
                std::cout << "Limit reached\n";
                assert(complex_eigenvalues != 500);
            }

        }
	}

	for (int i = 0; i < m_2->get_width(); i++) {
		eigenvalues.emplace_back(  round( m_2->get_element(i, i) * 1000 ) / 1000 - shift );
	}

	return eigenvalues;

}

Matrix* eigen_vectors(Matrix* matrix, std::vector<double>* eigenvalues) {
    int size = matrix->get_height();
	assert( check_square(matrix) );
	assert( eigenvalues->size() == size );

	Matrix* result = new Matrix( size, size );
	Matrix* maket;

	for (int i = 0; i < eigenvalues->size(); i++){
	    maket = add_matrix(matrix, identity( size ), 1, -(*eigenvalues)[i] );
	    maket = solve_homogoeneous_equation(maket);

	    for (int j = 0; j < maket->get_height(); j++){
	        if ( maket->get_element(j, 0) == -1 ){
                result->set_element(j, i, 1);
	        } else{
                result->set_element(j, i, maket->get_element(j, 0));
	        }
	    }
	}

    return result;
}

Matrix* solve_homogoeneous_equation(Matrix *m){
    assert( check_square(m) );
//    auto m_2 = row_echelon( m );
//    m_2 = rref(m);
    auto m_2 = m->copy();
    int trace_size = 0;

    for (int i = 0; i < m_2->get_width(); i++ ){
        if ( i < m_2->get_width() && i < m_2->get_height() ){
            trace_size += m_2->get_element(i, i);
        } else {
            break;
        }
    }

//    Only trivial solution
    if ( trace_size == m_2->get_width() && trace_size == m_2->get_height() ){
        std::cout << "System has only trivial solution \n";
        return new Matrix( m_2->get_height(), 1 );
    }

    auto result_matrix = new Matrix( m_2->get_height(), m_2->get_width() - trace_size );

    for (int i = 0; i < result_matrix->get_height(); i++){
        for (int j = 0; j < result_matrix->get_width(); j++){
            result_matrix->set_element(i, j, -1 );
        }
    }

    for (int i = 0; i < trace_size; i++){
        for (int j = 0; j < result_matrix->get_width(); j++){
            result_matrix->set_element(i, j, - m->get_element(i, j + trace_size) );
        }
    }

    std::cout << "-1 means free variable which should be mentioned as x, y etc. And numbers are coefficients"
                 " near variables\n";
    return result_matrix;
}

Matrix* generate_transition_matrix(Matrix* old_basis, Matrix* new_basis){
    assert( check_square(old_basis) );
    assert( check_square(new_basis) );
    assert( old_basis->get_width() == new_basis->get_width() );
    assert( determinant(old_basis) != 0 && determinant(new_basis) != 0 );

    double coef, coef_2;

    for(int i = 0; i <  new_basis->get_width() ; i++){
        coef = new_basis->get_element(i, i);

        for (int j = 0; j < new_basis->get_width(); j++){
            new_basis->set_element(i, j, new_basis->get_element(i,j) / coef );
            old_basis->set_element(i, j, old_basis->get_element(i,j) / coef );
        }

        for (int j = 0; j < new_basis->get_width(); j++){
            coef_2 = j == i ? 0: new_basis->get_element(j, i);
            new_basis->add_to_row(j, i, -coef_2);
            old_basis->add_to_row(j, i, -coef_2);
        }
    }
    return old_basis;
}

Matrix* change_of_basis(Matrix* transition_matrix, Matrix* vector){
    assert( check_square(transition_matrix) && determinant(transition_matrix) != 0 );
    assert(vector->get_height() == transition_matrix->get_height() && vector->get_width() == 1);

    auto result_matrix = multiply_matrix(transition_matrix, vector);
    return result_matrix;
}

void multiply_matrix_row(Matrix* m, int row, double multiplier){
    assert( row >= 0 && row < m->get_height() );
    double new_value;

    for (int i = 0; i < m->get_width(); i++){
        new_value = m->get_element(row, i) * multiplier;
        m->set_element( row, i,  new_value);
    }
}

double get_first_nonzero_entry(Matrix* m, int row){
    assert( row >= 0 && row < m->get_height() );
    double result = 0;

    for (int i = 0; i < m->get_width(); i++){
        if ( m->get_element(row, i) != 0 ){
            result = m->get_element(row, i);
            return result;
        }
    }

    return result;
}