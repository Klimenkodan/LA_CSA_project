
#ifndef LA_CSA_PROJECT_MATRIX_OPERATIONS_H
#define LA_CSA_PROJECT_MATRIX_OPERATIONS_H

#endif //LA_CSA_PROJECT_MATRIX_OPERATIONS_H

#include <iostream>
#include "matrix.h"

bool sizes_equal(const Matrix* a, const Matrix* b);

Matrix* add_matrix(Matrix* a, Matrix* b);

Matrix* subtract_matrix(Matrix* a, Matrix* b);

Matrix* multiply_matrix(Matrix* a, Matrix* b);

Matrix* scalar_multiply(Matrix* a, double mul);

Matrix* row_echelon(Matrix* a);

int rank(Matrix * a);

Matrix* inverse(Matrix* a);

Matrix* identity(int num_rows); // need to be deleted

Matrix* solve_equation(Matrix* matrix, Matrix* vector);

Matrix* transpose(Matrix* m);

double determinant(Matrix* matrix);
