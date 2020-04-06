
#ifndef LA_CSA_PROJECT_MATRIX_OPERATIONS_H
#define LA_CSA_PROJECT_MATRIX_OPERATIONS_H

#endif //LA_CSA_PROJECT_MATRIX_OPERATIONS_H

#include <iostream>
#include "matrix.h"

double add_or_subtract(double a, double b, bool add);

bool sizes_equal(const Matrix* a, const Matrix* b);

Matrix* add_subtract(Matrix *a, Matrix *b, bool add);

Matrix* add_matrix(Matrix* a, Matrix* b);

Matrix* subtract_matrix(Matrix* a, Matrix* b);

Matrix* multiply_matrix(Matrix* a, Matrix* b);
