#ifndef LA_CSA_PROJECT_MATRIX_H
#define LA_CSA_PROJECT_MATRIX_H

#include <cstddef>
#include <string>
#include <iostream>

class Matrix {
public:
	int weight;
	int height;
	double* matrix;
	Matrix(int m, int n) {
		if (m == 0 || n == 0) {
			std::cout<< "matrix can not be of size 0" << std::endl;
			throw;
		}
		matrix = new double[m * n];
		weight = n;
		height = m;
	}

	double get_element(int row_num, int col_num);

	void set_element(int row_num, int col_num, double el);

	void scalar_multiply(double scalar);

	std::string representation();
};


#endif //LA_CSA_PROJECT_MATRIX_H
