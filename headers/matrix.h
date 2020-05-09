#ifndef LA_CSA_PROJECT_MATRIX_H
#define LA_CSA_PROJECT_MATRIX_H

#include <cstddef>
#include <string>
#include <iostream>
#include <vector>

class Matrix {
private:
	int width;
	int height;
	double* matrix;

public:

	Matrix(int m, int n);

	Matrix(int m, int n, const std::vector<double>& values);

	int get_width() {
		return width;
	}

	int get_height() {
		return height;
	}

	double get_element(int row_num, int col_num);

	void set_element(int row_num, int col_num, double el);

	bool equal(Matrix* b, double err);

	void scalar_multiply(double scalar);

	void add_column(Matrix* column, int num_column);

	void interchange_rows(int row_1, int row_2);

	void add_to_row(int row_to, int row_that, double coeff);

	void multiply_row(int row, double coeff);

	Matrix* copy();

	Matrix* copy_column(int col_num);

	Matrix* copy_row(int row_num);

	std::string representation();
};


#endif //LA_CSA_PROJECT_MATRIX_H
