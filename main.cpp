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

//    Matrix m_1 = Matrix( 6,3, {5,6,7,1,3,7,10,11,16,17,21,23,29,8,3,0,1,2} );
//

//    Matrix m_1 = {3, 3, {
//        -5, -4, 2,
//        0, -0.4, 1.2,
//        0, 0, 0
//    }};
//    Matrix m_1 = Matrix(3,3, {
//            -5, -4, 2,
//            0, -0.4, 1.2,
//            0, 0,0
//    });
//
//    std::cout << m_1.representation() << "\n";
//    m_1 = *rref(&m_1);
//    std::cout << m_1.representation() << "\n";
//    std::cout << rref( &m_1 )->representation() << "\n";


}