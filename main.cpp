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

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

//    Matrix m_1 = Matrix(3,3, {1,2,3,6,5,4,9,5,7});
//    Matrix vector = Matrix(3,1, {1,2,3});
//
//    auto m_2 = change_of_basis(&m_1, &vector);

//    std::cout << determinant(&m_1) << "\n";
//    std::cout << m_1.representation() << "\n";
//    std::cout << determinant(&old);

//    std::cout << m_2->representation() << "\n";
}