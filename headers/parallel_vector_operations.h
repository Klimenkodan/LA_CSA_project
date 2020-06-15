#ifndef LA_CSA_PROJECT_PARALLEL_VECTOR_OPERATIONS_H
#define LA_CSA_PROJECT_PARALLEL_VECTOR_OPERATIONS_H

//#include <cstdint>
#include "matrix.h"

bool collinear_parallel(Matrix*a , Matrix* b, int threadN, int task_partition);
double dot_product_parallel(Matrix*a , Matrix* b, int threadN, int task_partition);
bool orthogonal_parallel(Matrix*a , Matrix* b, int threadN, int task_partition);
double norm_prl (Matrix* matrix, int threadN, int task_partition);


#endif //LA_CSA_PROJECT_PARALLEL_VECTOR_OPERATIONS_H
