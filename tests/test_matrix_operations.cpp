#include <functional>
#include <assert.h>
#include "test_matrix_operations.h"
#include "../headers/matrix.h"
#include "../headers/matrix_operations.h"

void test_row_ech() {
	double precession = 0.0005;
	std::vector<double> matr = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	auto* matrix = new Matrix(3, 3, std::ref(matr));
	assert(matrix->equal(row_echelon(matrix), precession));
	matr = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	matrix = new Matrix(3, 4, std::ref(matr));
	assert(matrix->equal(row_echelon(matrix), precession));
//	matr = {};
	matrix = new Matrix(3, 4, std::ref(matr));
}

void test_rref() {
	double precession = 0.00005;
	Matrix* result;
	std::vector<double> matr = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	auto* matrix = new Matrix(3, 3, std::ref(matr));
	assert(matrix->equal(row_echelon(matrix), precession));

	matr = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	matrix = new Matrix(3, 4, std::ref(matr));
	assert(matrix->equal(row_echelon(matrix), precession));

	matr = {1, 5, 1, 2, 11, 5};
	matrix = new Matrix(2, 3, std::ref(matr));
	matr = {1, 0, -14, 0, 1, 3};
	result = new Matrix(2, 3, std::ref(matr));
	assert(rref(matrix)->equal(result, precession));

	matr = {0, 58, 56, 0, 0, 23};
	matrix = new Matrix(2, 3, std::ref(matr));
	matr = {0, 1, 0, 0, 0, 1};
	result = new Matrix(2, 3, std::ref(matr));
	assert(rref(matrix)->equal(result, precession));

	matr = {12, 23, 34, 56, 12, 23, 34, 56, 12, 23, 34, 56};
	matrix = new Matrix(3, 4, std::ref(matr));
	matr = {1, 1.916667, 2.833333, 4.6666667, 0, 0, 0, 0, 0, 0, 0, 0};
	result = new Matrix(3, 4, std::ref(matr));
//	std::cout << rref(matrix)->representation() << std::endl;
//	std::cout << result->representation() << std::endl;
	assert(rref(matrix)->equal(result, precession));

	matr = {0, 0, 0, 0, 0, 0, 0, 0, 12, 23, 34, 56};
	matrix = new Matrix(3, 4, std::ref(matr));
	matr = {1, 1.916667, 2.833333, 4.6666667, 0, 0, 0, 0, 0, 0, 0, 0};
	result = new Matrix(3, 4, std::ref(matr));
	assert(rref(matrix)->equal(result, precession));

}

bool test_matrix_op() {
	using std::cout;
	using std::endl;
	test_row_ech();
	cout << "row_ech is ok" << endl;
	test_rref();
	cout << "rref is ok" << endl;

}




//bool test() {
//	using std::cout;
//	using std::endl;
//	test_add_column();
//	cout << "add_column is okay" << endl;
//	test_add_to_row();
//	cout << "add_to_row is okay" << endl;
//	test_equal();
//	cout << "equal is okay" << endl;
//	test_copy_row();
//	cout << "copy_row is okay" << endl;
//	test_from_array();
//	cout << "from array is okay" << endl;
//	test_interchange_rows();
//	cout << "interchange rows is okay" << endl;
//	cout << "everything is okay" << endl;
//	return true;
//
//}
