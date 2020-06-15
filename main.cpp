#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <cassert>
#include "headers/matrix.h"
#include "headers/matrix_operations.h"
#include "helper_functions/helper_functions.h"
#include "headers/vector_operations.h"
#include "tests/test_matrix.h"
#include "tests/test_matrix_operations.h"



int main() {
	using std::cout;
	using std::endl;
	auto matrix = Matrix(3, 3, {0, 2, 3, 0, 2, 0, 1, 0, 0});
	Matrix m_1 =Matrix(3, 3, {
			1, 2, 3,
			2, 7, 8,
			3, 8, 3
	});
	Matrix m_2 = Matrix(5, 5, {
			1, 2, 3, 4, 5,
			6, 7, 8, 9, 0,
			5, 4, 3, 2, 1,
			2, 2, 5, 6, 0,
			1, 5, 8, 2, 9
	});
	cout << multiply_matrix(&m_2, inv(&m_2))->representation();
//	std::vector<double> i = qr_method_eigenvalues(&m_1);
//	for (auto b: i) {
//		cout << b << endl;
//	}
//	cout <<row_echelon(&matrix)->representation();
	return 0;
}