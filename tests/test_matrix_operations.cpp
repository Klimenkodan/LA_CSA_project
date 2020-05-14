#include "../headers/matrix_operations.h"
#include "../helper_functions/helper_functions.h"
#include "../headers/vector_operations.h"
#include "../tests/test_matrix.h"
#include "../tests/test_matrix_operations.h"
#include <gtest/gtest.h>

TEST(sizes_equal_test, unexpected_args){
    Matrix m_1 = Matrix(5,4);
    Matrix m_2 = Matrix(5,4);

    ASSERT_TRUE(sizes_equal( &m_1,  &m_2 ));
    ASSERT_FALSE(sizes_equal( new Matrix(5,4),  new Matrix(4,5) ));

    ASSERT_TRUE( sizes_equal( new Matrix(1,1),  new Matrix(1,1) ) );
    ASSERT_TRUE( sizes_equal( new Matrix(1,1, {2}),  new Matrix(1,1, {3}) ) );

    ASSERT_TRUE( sizes_equal( new Matrix(1,1),  new Matrix(1,1, {5} ) ) );
    ASSERT_TRUE( sizes_equal( new Matrix(2,3),  new Matrix(2,3, {1,1,2,3,4,5} ) ) );

    ASSERT_DEATH( sizes_equal( new Matrix(0,2),  new Matrix(2,0, {1,1} ) ), "" );
    ASSERT_FALSE( sizes_equal( new Matrix(3,2),  new Matrix(2,3, {1,1,2,3,4,5} ) ) );

    m_1.add_column( new Matrix(5, 1, {1,1,1,1,1}),0 );
    m_1.add_column( new Matrix(5, 1, {1,1,1,1,1}),3 );
    m_2.add_to_row(1,2,3);
    m_2.multiply_row(0, -5);

    ASSERT_TRUE(sizes_equal( &m_1,  &m_2 ) );
    m_1.interchange_rows(0,2);

    ASSERT_TRUE( sizes_equal( &m_1,  &m_2 ) );
}

TEST(add_matrix_test, unexpected_args){
    Matrix m_1 = Matrix(4,2, {1,1,1,1,1,1,1, 1});
    Matrix m_2 = Matrix(4,2,{2,2,2,2,2,2,2,2});
    Matrix m_4 = Matrix(4,2, {3,3,3,3,3,3,3,3});

    auto m_3 = add_matrix(&m_1, &m_2, 1, 1);
    for(int i = 0; i < m_1.get_width(); ++i){
        for(int j = 0; j < m_1.get_height(); ++j){
            ASSERT_EQ( m_4.get_element(j, i), m_3->get_element(j,i) );
        }
    }

    m_1 = Matrix(2,4);
    ASSERT_DEATH( add_matrix(&m_1, &m_2, 1, 1), "");
    ASSERT_DEATH(add_matrix(&m_2, &m_1, 1, 1), "");

    m_1 = Matrix(2,3, {1,2,3,4,5,6});
    m_2 = Matrix(2,3);

    m_4 = Matrix(2, 3, {2,4,6,8,10,12});
    m_3 = add_matrix(&m_1, &m_2, 2, 3);

    for(int i = 0; i < m_1.get_width(); ++i){
        for(int j = 0; j < m_1.get_height(); ++j){
            ASSERT_EQ( m_4.get_element(j, i), m_3->get_element(j,i) );
        }
    }

    m_1 = Matrix(5,5);
    m_2 = Matrix(5,5);
    m_3 = add_matrix(&m_1, &m_2, 5, 10);

    for(int i = 0; i < m_1.get_width(); ++i){
        for(int j = 0; j < m_1.get_height(); ++j){
            ASSERT_EQ( m_3->get_element(j, i), 0 );
        }
    }
}

TEST(multiply_matrix_test, unexpected_args) {
    Matrix m_1 = Matrix(2, 2, {3, 4, 5, 6});
    Matrix m_2 = Matrix(2, 5, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    auto m_3 = multiply_matrix(&m_1, &m_2);
    ASSERT_EQ(multiply_matrix(&m_2, &m_1), nullptr);

    ASSERT_EQ(m_3->get_height(), 2);
    ASSERT_EQ(m_3->get_width(), 5);

    m_3 = new Matrix(2, 5, {27, 34, 41, 48, 55, 41, 52, 63, 74, 85});
    ASSERT_TRUE(m_3->equal(new Matrix(2, 5, {27, 34, 41, 48, 55, 41, 52, 63, 74, 85}), 0.0001));
}

TEST(identity_matrix_test, unexpected_args){
    auto m_1 = identity(5);
    int ones = 0;

    ASSERT_EQ(m_1->get_width(), m_1->get_height());

    for (int i = 0; i < m_1->get_width(); i++){
        for (int j = 0; j < m_1->get_height(); j++){
            if (m_1->get_element(i, j) != 0) {
                ASSERT_EQ(i, j);
                ones++;
            }
        }
    }
    ASSERT_EQ(m_1->get_width(), ones);
}

TEST(scalar_multiply_test, unexpected_args){
    int sc = 0;
    Matrix m_1 = Matrix(2,3, {4,3,2,1,0,-1});
    auto m_2 = scalar_multiply(&m_1, sc);

    for (int i = 0; i < m_1.get_height(); ++i ){
        for (int j = 0; j < m_1.get_width(); ++j) {
            ASSERT_EQ(m_2->get_element(i, j), m_1.get_element(i, j) * sc );
        }
    }
}

//TEST(row_echelon_test, unexpected_args){
//
//    Matrix m_1 = Matrix(2,2, {2,4,5,6});
//    Matrix m_2 = Matrix(2,2, {2,4,0,-4});
//
//    ASSERT_TRUE(row_echelon( &m_1 )->equal(&m_2, 000.1));
//
//    m_1 = Matrix(3,4, {2,5,6,7,8,9,10,11,15,14,13,12});
//    m_1 = *row_echelon(&m_1);
//
//    ASSERT_EQ(m_1.get_element())
//}