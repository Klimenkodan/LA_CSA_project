#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include "headers/matrix.h"
#include "headers/matrix_operations.h"
#include "helper_functions/helper_functions.h"
#include "headers/vector_operations.h"
#include "tests/test_matrix.h"
#include "tests/test_matrix_operations.h"
#include <gtest/gtest.h>


int main(int argc, char **argv) {
//	using std::cout;
//	using std::endl;
//	auto* a = new Matrix(3, 4);
//	auto* a = read_matrix_conf(3, 4, "conf1.txt");
//	auto* b = read_matrix_conf(3, 3, "conf.txt");
//	std::vector<double> eig = qr_method_eigenvalues(b);
//	for (auto c: eig) {
//		cout << c << endl;
//	}
//	cout << b->representation() << endl;
//	Matrix* eigvc = eigen_vectors(b, std::ref(eig));
//	cout << eigvc->representation() << endl;
//	cout << row_echelon(a)->representation() << endl;
//	bool x = 0 == 1;
//	cout << x;
//	test_matrix_op();
//	Matrix* mat = a->copy_row(2);
//	a->interchange_rows(0, 0);
//	a->add_to_row(0,1, 2);
//	cout << a->representation();
//	std::vector<double> hs;
//	test();
////	double* r = {};
//	r[1] = 3;
//	r[2] = 6;

//	hs[0] = 12;
//	cout << hs.at(2);
//	Matrix* mat = inverse(b);
//	cout << mat->representation();

//	std::map<std::string, Matrix*> maps = QR_factorization(a);
//	cout << maps["Q"]->representation() << endl;
//	cout << maps["R"]->representation() << endl;
//	cout << multiply_matrix(maps["Q"], maps["R"])->representation() << endl;

//	auto* b = new Matrix(1, 3);
//	b->set_element(0, 0, 1);
//	b->set_element(0, 1, 1);
//	b->set_element(0, 2, 1);
//	std::cout << transpose(b)->representation();

//  Google Tests starting

//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

//    Matrix m_1 = Matrix(3,4, {2,5,6,7,8,9,10,11,15,14,13,12});
    auto m_1 = Matrix(3,4, {2,5,6,7,8,9,10,11,15,14,13,12});
    m_1 = *row_echelon(&m_1);
    std::cout << m_1.representation();

    for (int i = 0; i < m_1.get_height() - 1; i++){
//        for (int j = i; j < m_1.get_height(); ++j) {
            std::cout << i << "\n";
//        }
    }

//    Matrix m_2 = Matrix(2,5, {1,2,3,4,5,6,7,8,9,10});
//
//    auto m_3 = multiply_matrix(&m_1, &m_2);
//
//    bool a = row_echelon( &m_1 )->get_element(2,2) == -2.09091;
//    std::cout << row_echelon(&m_1)->representation() << "\n";
//    return 0;
}