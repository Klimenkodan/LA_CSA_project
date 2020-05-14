//#include <functional>
//#include "test_matrix_operations.h"
//#include "../headers/matrix.h"
//#include "../headers/matrix_operations.h"
//#include <gtest/gtest.h>
//#include <vector>
//
//TEST(test_constructor_1, different_start_values){
//    ASSERT_DEATH( new Matrix(-5, -5), "" );
//    ASSERT_DEATH( new Matrix(0, 0),"" );
//
//    ASSERT_DEATH( new Matrix(-5, 0), "" );
//    ASSERT_DEATH(  new Matrix(0, -5), "" );
//
//    ASSERT_DEATH( new Matrix(5, 0), "" );
//    ASSERT_DEATH( new Matrix(0, 5), "" );
//
//    ASSERT_NO_THROW( new Matrix(5, 2) );
//    ASSERT_NO_THROW( new Matrix(2, 5) );
//
//    ASSERT_NE( new Matrix(5, 2), new Matrix(2, 5) );
//    ASSERT_NE( new Matrix(2,2), new Matrix(2, 2) );
//}
//
//TEST(test_constructor_2, different_start_values){
//    std::vector<double> arr = {1,2,3,4};
//    auto m_1 = Matrix(4, 1, arr);
//
//    ASSERT_DEATH( new Matrix(4, 0, arr), "" );
//    ASSERT_DEATH( new Matrix(4, 2, arr), "" );
//
//    ASSERT_DEATH( new Matrix(3, 1, arr), "" );
//    ASSERT_DEATH( new Matrix(3, 0, arr), "" );
//
//    std::vector<double> arr_2 = {};
//    ASSERT_DEATH( new Matrix(0, 0, arr_2), "" );
//    ASSERT_DEATH( new Matrix(-1, 2, arr_2), "" );
//
//    ASSERT_DEATH( new Matrix(1, 1, arr_2), "" );
//    ASSERT_NO_THROW( new Matrix(4, 1, arr) );
//
//    ASSERT_NO_THROW( new Matrix(1, 4, arr) );
//    ASSERT_NO_THROW( new Matrix(2, 2, arr) );
//
//    for ( int i = 0; i < m_1.get_height(); i++ ){
//        for ( int k = 0; k < m_1.get_width(); k++ ){
//            ASSERT_EQ( m_1.get_element(i, k), arr[i] );
//        }
//    }
//}
//
//TEST(get_element_test, unexpected_args){
//
//    std::vector<double> arr = {1,2,3,4,5,6};
//    auto m_1 = Matrix(6, 1, arr);
//
//    for ( int i = 0; i < m_1.get_height(); i++ ){
//        for ( int k = 0; k < m_1.get_width(); k++ ){
//            ASSERT_EQ( m_1.get_element(i, k), arr[i] );
//        }
//    }
//
//    auto m_2 = Matrix(1, 6, arr);
//    for ( int i = 0; i < m_2.get_height(); i++ ){
//        for ( int k = 0; k < m_2.get_width(); k++ ){
//            ASSERT_EQ( m_2.get_element(i, k), arr[k] );
//        }
//    }
//
//    ASSERT_DEATH( m_2.get_element(0, -1), "" );
//    ASSERT_DEATH( m_2.get_element(-2, -2), "" );
//
//    ASSERT_DEATH( m_2.get_element(0, 7), "" );
//    ASSERT_DEATH( m_2.get_element(5, 5), "" );
//}
//
//TEST(set_element_test, unexpected_args){
//    auto m_1 = Matrix(5, 1);
//    std::vector<double> result_arr = {1,2,3,4,5,6};
//
//    for (int i = 0; i < m_1.get_height(); i++ ){
//        for ( int k = 0; k < m_1.get_width(); k++ ){
//            m_1.set_element( i, k, result_arr[i] );
//            ASSERT_EQ(m_1.get_element(i, k), result_arr[i]);
//        }
//    }
//
//    ASSERT_DEATH(m_1.set_element(0, -1, 0), "");
//    ASSERT_DEATH(m_1.set_element(-2, -5, 0), "");
//
//    ASSERT_DEATH( m_1.set_element(m_1.get_height(), m_1.get_width(), 0), "" );
//    ASSERT_DEATH( m_1.set_element(m_1.get_width(), m_1.get_height(), 0), "" );
//
//    ASSERT_NO_THROW(m_1.set_element(0, 0, 1));
//}
//
//TEST(scalar_multiply_test, unexpected_args){
//    std::vector<double> ar_1 = {1,2,3,4,5,6};
//    Matrix m_1 = Matrix(6, 1, ar_1);
//
//    int scalar = 5;
//    m_1.scalar_multiply(scalar);
//
//    for (int i = 0; i < m_1.get_height(); ++i) {
//        for (int k = 0; k < m_1.get_width(); ++k) {
//            ASSERT_EQ(m_1.get_element(i, k), ar_1[i] * scalar );
//        }
//    }
//}
//
//TEST(copy_column_test, unexpected_args){
//    std::vector<double> ar_1 = {1,2,3,4,5,6};
//    Matrix m_1 = Matrix(2, 3, ar_1);
//
//    auto column = m_1.copy_column(0);
//
//    for (int i = 0; i < column->get_height(); ++i) {
//        for (int j = 0; j < column->get_width(); ++j){
//            ASSERT_EQ( m_1.get_element(i, j), column->get_element(i, 0) );
//        }
//    }
//
//    ASSERT_DEATH( m_1.copy_column( m_1.get_width() ), "" );
//    ASSERT_DEATH( m_1.copy_column( 20 ), "" );
//
//    ASSERT_DEATH( m_1.copy_column( -1 ), "" );
//    ASSERT_EQ(m_1.copy_column( 0 )->get_height(), m_1.get_height() );
//}
//
//TEST(representation_test, unexpected_args){
//
//    Matrix m = Matrix(2,3, {1,2,3,4,5,6});
//    ASSERT_EQ( "| 1 2 3 |\n| 4 5 6 |\n", m.representation() );
//
//    m.get_element(0, 0);
//    ASSERT_EQ( "| 1 2 3 |\n| 4 5 6 |\n", m.representation() );
//
//    m.set_element(0, 0, 0);
//    ASSERT_NE("| 1 2 3 |\n| 4 5 6 |\n", m.representation());
//}
//
//TEST(copy_test, unexpected_args){
//    Matrix m_1 = Matrix(2, 3, {6,5,4,3,2,1} );
//    Matrix *k_1 = m_1.copy();
//
//    Matrix m_2 = Matrix(2,3);
//    Matrix *k_2 = m_2.copy();
//
//    for (int i = 0; i < m_1.get_height(); ++i) {
//        for (int j = 0; j < m_1.get_width(); ++j){
//            ASSERT_EQ( m_1.get_element(i, j), k_1->get_element(i, j) );
//            ASSERT_EQ( m_2.get_element(i, j), k_2->get_element(i, j) );
//        }
//    }
//}
//
//TEST(equal_test, unexpected_args){
//    Matrix m = Matrix(5,2, {9,8,7,6,5,4,3,2,1,0});
//    Matrix m_2 = Matrix(5,2, {9,8,7,6,5,4,3,2,1,1});
//    Matrix k = Matrix(2,5, {9,8,7,6,5,4,3,2,1,0});
//    Matrix *m_1 = m.copy();
//    Matrix *k_1 = k.copy();
//
//    ASSERT_TRUE(m.equal(m_1, 0.0001) );
//    ASSERT_TRUE(k.equal(k_1, 0.0001) );
//
//    ASSERT_DEATH(m.equal(&k, 0.001), "");
//    ASSERT_DEATH(k.equal(&m, 0.001), "");
//
//    ASSERT_FALSE(m.equal(&m_2, 0.001) );
//}
//
//TEST(add_column_test, unexpected_args){
//
//    Matrix m = Matrix(4,2, {1,2,3,4,5,6,7,8});
//    Matrix m_2 = Matrix(4,1, {4,3,2,1});
//
//    m.add_column(&m_2, 0);
//    std::vector<double> arr = {4,3,2,1};
//
//    for (int i = 0; i < m.get_height(); i++){
//        ASSERT_EQ( m.get_element(i, 0), arr[i] );
//    }
//
//    Matrix m_3 = Matrix(2,2);
//
//    ASSERT_DEATH( m.add_column(&m_3, 0), "" );
//    ASSERT_DEATH( m.add_column(&m_2, -2), "" );
//    ASSERT_DEATH( m.add_column(&m_2, 5), "" );
//}
//
//TEST(interchange_rows_test, unexpected_args){
//
//    Matrix m_1 = Matrix(2,4, {1,2,3,4,5,6,7,8});
//    std::vector<double> ar_1 = {5,6,7,8};
//    std::vector<double> ar_2 = {1,2,3,4};
//
//    m_1.interchange_rows(0, 1);
//
//    for( int i = 0; i < m_1.get_width(); ++i){
//        ASSERT_EQ(m_1.get_element(0, i), ar_1[i] );
//        ASSERT_EQ(m_1.get_element(1, i), ar_2[i] );
//    }
//
//    ASSERT_DEATH(m_1.interchange_rows(-1, 0), "");
//    ASSERT_DEATH(m_1.interchange_rows(5,5), "");
//    ASSERT_NO_THROW(m_1.interchange_rows(0, 0));
//}
//
//TEST(copy_rows_test, unexpected_args){
//    Matrix m = Matrix(2, 4, {8,7,6,5,4,3,2,1} );
//    auto m_1 = m.copy_row(0);
//    std::vector<double> arr = {8,7,6,5};
//
//    for ( int i = 0; i < m.get_width(); ++i ){
//        ASSERT_EQ( m_1->get_element(0, i), arr[i] );
//    }
//
//    ASSERT_DEATH( m.copy_row(-5), "" );
//    ASSERT_DEATH( m.copy_row( m.get_height() ), "" );
//
//    ASSERT_NO_THROW( Matrix(5, 5).copy_row(1) );
//}
//
//TEST(add_to_row_test, unexpected_args){
//    Matrix m = Matrix(5,5);
//
//    ASSERT_NO_THROW(m.add_to_row(0, 0, 2));
//    ASSERT_NO_THROW(m.add_to_row(0, 0, -5));
//
//    ASSERT_DEATH(m.add_to_row(0, 6, 9), "");
//    ASSERT_DEATH(m.add_to_row(0, -2, 1), "");
//
//    m = Matrix(2,4,{1,2,3,4,5,6,7,8});
//    std::vector<double> arr = {11,14,17,20};
//
//    m.add_to_row(0, 1, 2);
//    for (int i = 0; i < m.get_width(); ++i) {
//        ASSERT_EQ(m.get_element(0, i), arr[i]);
//    }
//}
//
//TEST(multiply_row_test, unexpected_args){
//
//    Matrix m_1 = Matrix(2,3, {1,2,3,4,5,6});
//    m_1.multiply_row(0, 4);
//
//    Matrix m_2 = Matrix(2,3, {1,2,3,4,5,6});
//    for(int i = 0; i < m_1.get_width(); i++){
//        ASSERT_EQ( m_1.get_element(0, i), m_2.get_element(0, i) * 4 );
//        ASSERT_EQ( m_1.get_element(1, i), m_2.get_element(1, i) );
//    }
//
//    ASSERT_DEATH( m_1.multiply_row( m_1.get_height(), 2 ), "" );
//    ASSERT_DEATH( m_1.multiply_row(m_1.get_height() + 1, 2), "" );
//
//    ASSERT_DEATH( m_1.multiply_row(-2, 2), "" );
//    ASSERT_NO_THROW( m_1.multiply_row(1, -2) );
//}