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
//  Google Tests starting

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

    auto Q = res["Q"];
    auto Q_in = inverse(Q);

    auto Q_trasp = transpose(Q);
    auto R = res["R"];

//    std::cout << multiply_matrix(Q,Q_in)->representation() << "\n";
//    std::cout << determinant(&m_1) << "\n";

//    std::cout << Q->representation() << "\n";
//    std::cout << inverse(Q)->representation() << "\n";

//    inverse(Q);
}