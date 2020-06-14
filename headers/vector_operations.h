#ifndef LA_CSA_PROJECT_VECTOR_OPERATIONS_H
#define LA_CSA_PROJECT_VECTOR_OPERATIONS_H

#endif //LA_CSA_PROJECT_VECTOR_OPERATIONS_H

#include <vector>
#include "matrix.h"

double dot_productV(std::vector<double>* a, std::vector<double>* b);

double dot_product(Matrix*a , Matrix* b);

bool is_vector( Matrix* a);

double orthogonalM(Matrix*a , Matrix* b);

double orthogonal(std::vector<double>* a, std::vector<double>* b);

double collinear_m(Matrix*a , Matrix* b);

double collinear_v(std::vector<double>* a, std::vector<double>* b);

double norm (Matrix* matrix);

bool is_zero_vector( Matrix* v );