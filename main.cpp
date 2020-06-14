#include <iostream>
#include <tgmath.h>

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
//  Google Tests starting

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

//    Matrix m_1 = Matrix(3, 3, {
//            0, 0, 0,
//            9, 4, 0,
//            0, 2, 0
//    });

//    Matrix m_1 = Matrix(3, 3, {
//            1, 0, 0,
//            9, 1, 0,
//            1, 2, 1});

//    Matrix m_1 = Matrix(3, 3, {
//            3,1,5,
//            0,4,1,
//            6,9,9
//    });
//
//    std::vector<double> e = qr_method_eigenvalues(&m_1);
//
//    auto result = eigen_vectors(&m_1,  &a);
//
//    std::cout << solve_homogoeneous_equation(&m_1)->representation() << "\n";

//    qr_method_eigenvalues(&m_1);
//
//    std::vector<double> e = qr_method_eigenvalues(&m_1);
//    for (auto x: e){
//        std::cout << x << "\n";
//    }
//    std::cout << transpose(&m_1)->representation() << "\n";
//    auto m = eigen_vectors(&m_1, &e);

//    for ( int i = 0; i < res.size(); i++ ){
//        std::cout <<  qr_method_eigenvalues(&m_1)[i] << " " << res[i] << "\n";
//    }
}