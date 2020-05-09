
#ifndef LA_CSA_PROJECT_MATRIX_OPERATIONS_H
#define LA_CSA_PROJECT_MATRIX_OPERATIONS_H

#endif //LA_CSA_PROJECT_MATRIX_OPERATIONS_H

#include <iostream>
#include "matrix.h"
#include <map>

Matrix* row_echelon(Matrix* matrix);

Matrix* rref(Matrix* matrix);

bool sizes_equal(const Matrix* a, const Matrix* b);

bool is_upper(Matrix* matrix);

Matrix* add_matrix(Matrix* a, Matrix* b, double a_coef, double b_coef);

Matrix* multiply_matrix(Matrix* a, Matrix* b);

Matrix* scalar_multiply(Matrix* a, double mul);

int rank(Matrix * a);

std::map<std::string, Matrix*> QR_factorization(Matrix* matrix);

Matrix* inverse(Matrix* a);

std::vector<double> qr_method_eigenvalues(Matrix* matrix);

Matrix* identity(int num_rows); // need to be deleted

Matrix* solve_equation(Matrix* matrix, Matrix* vector);

Matrix* transpose(Matrix* m);

double determinant(Matrix* matrix);

double trace(Matrix* matrix);

Matrix* eigen_vectors(Matrix* matrix, const std::vector<double>& eigenvalues);