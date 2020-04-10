#ifndef LA_CSA_PROJECT_MATRIX_H
#define LA_CSA_PROJECT_MATRIX_H

#include <cstddef>
#include <string>
#include <iostream>

class Matrix {
public:
	int width;
	int height;
private:
	double* matrix;
public:

	Matrix(int m, int n);

	double get_element(int row_num, int col_num);

	void set_element(int row_num, int col_num, double el);

	bool equal(Matrix* b);

	void scalar_multiply(double scalar);

	Matrix* copy();

	std::string representation();
};


#endif //LA_CSA_PROJECT_MATRIX_H
