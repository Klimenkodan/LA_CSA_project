#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include "headers/matrix.h"
#include "headers/matrix_operations.h"
#include "helper_functions/helper_functions.h"
#include "headers/vector_operations.h"
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
//
//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

    Matrix m_1 = Matrix(5, 5, {
            1, 2, 3, 4, 5,
            6, 7, 8, 9, 0,
            5, 4, 3, 2, 1,
            2, 2, 5, 6, 0,
            1, 5, 8, 2, 9
    });

    auto res = QR_factorization(&m_1);
    auto f = inverse(res["Q"]);
//
    std::cout << multiply_matrix(f, res["Q"])->representation()<< "\n";
    std::cout << res["Q"]->representation() << "\n";
    std::cout << inverse(res["Q"])->representation() << "\n";
//    std::cout << res["R"]->representation();
//    Matrix m_1 = Matrix( 3,3, {1,2,3,4,5,6,7,8,9} );
//    auto res = QR_factorization(&m_1);
//    auto Q = res["Q"];
//
//    auto Q_in = inverse(Q);
//    bool r = identity(3)->equal(multiply_matrix(Q,Q_in), 0.1);
//    bool r_1 = is_upper(res["R"]);
//    std::cout << r << "\n";
//    std::cout << r_1 << "\n";


    return 0;
}