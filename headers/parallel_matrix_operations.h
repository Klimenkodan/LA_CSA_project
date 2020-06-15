#ifndef LA_CSA_PROJECT_PARALLEL_MATRIX_OPERATIONS_H
#define LA_CSA_PROJECT_PARALLEL_MATRIX_OPERATIONS_H

#include "matrix.h"



double determinant_parallel(Matrix* matrixx, int threadN, int task_partition);
double trace_parallel(Matrix* matrix, int threadN, int task_partition);
Matrix* add_matrix_parallel(Matrix* a, Matrix* b, double a_coef, double b_coef, int threadN);
Matrix* scalar_multiply_parallel(Matrix* a, double mul, int threadN);
Matrix* multiply_matrix_parallel(Matrix* a , Matrix* b, int threadN);
Matrix* change_of_basis_parallel(Matrix* transition_matrix, Matrix* vector, int threadN, int task_partition);

#endif //LA_CSA_PROJECT_PARALLEL_MATRIX_OPERATIONS_H
