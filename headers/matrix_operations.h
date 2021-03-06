
#ifndef LA_CSA_PROJECT_MATRIX_OPERATIONS_H
#define LA_CSA_PROJECT_MATRIX_OPERATIONS_H

#endif //LA_CSA_PROJECT_MATRIX_OPERATIONS_H

#include <iostream>
#include "matrix.h"
#include <map>

Matrix* inverse(Matrix* matrix1);

Matrix* row_echelon(Matrix* matrix);

Matrix* rref(Matrix* matrix);

bool sizes_equal(Matrix* a, Matrix* b);

bool is_upper(Matrix* matrix);

bool check_square(Matrix* matrix);

Matrix* add_matrix(Matrix* a, Matrix* b, double a_coef, double b_coef);

Matrix* multiply_matrix(Matrix* a, Matrix* b);

Matrix* scalar_multiply(Matrix* a, double mul);

int rank(Matrix * a);

std::map<std::string, Matrix*> QR_factorization(Matrix* matrix);

std::vector<double> qr_method_eigenvalues(Matrix* matrix);

Matrix* identity(int num_rows);

Matrix* solve_equation(Matrix* matrix, Matrix* vector);

Matrix* transpose(Matrix* m);

double determinant(Matrix* matrix);

double trace(Matrix* matrix);

Matrix* eigen_vectors(Matrix* matrix, std::vector<double>* eigenvalues);

Matrix* solve_homogoeneous_equation(Matrix *m);

Matrix* generate_transition_matrix(Matrix* m_1, Matrix* m_2);

Matrix* change_of_basis(Matrix* transition_matrix, Matrix* vector);

void round_matrix(Matrix* arg);

void multiply_matrix_row(Matrix* m, int row, double multiplier);

double get_first_nonzero_entry(Matrix* m, int row);