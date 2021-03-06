#ifndef LA_CSA_PROJECT_VECTOR_OPERATIONS_H
#define LA_CSA_PROJECT_VECTOR_OPERATIONS_H

#endif //LA_CSA_PROJECT_VECTOR_OPERATIONS_H

#include <vector>
#include "matrix.h"

double dot_productV(const std::vector<double>& a, const std::vector<double>& b);

double dot_product(Matrix*a , Matrix* b);

bool is_vector( Matrix* a);

bool orthogonalM(Matrix*a , Matrix* b);

bool orthogonal(std::vector<double>* a, std::vector<double>* b);

bool collinear_m(Matrix*a , Matrix* b);

bool collinear_v(std::vector<double>* a, std::vector<double>* b);

double norm (Matrix* matrix);

