#include <functional>
#include "../headers/matrix.h"
#include "../headers/vector_operations.h"
#include <gtest/gtest.h>
#include <vector>
#include <math.h>

TEST(is_a_vector_test, unexpected_args){
    ASSERT_TRUE(is_vector( new Matrix(1,2) ));
    ASSERT_TRUE(is_vector( new Matrix(2,1) ));

    ASSERT_FALSE( is_vector( new Matrix(2,3) ) );
    ASSERT_FALSE( is_vector( new Matrix(3,2) ) );

    ASSERT_DEATH( is_vector( new Matrix(2,0) ), "" );
    ASSERT_DEATH( is_vector( new Matrix(0,2) ), "" );
}

TEST(dot_productV_test, unexpected_args){
    std::vector<double> v_1 = {1,2,3};
    std::vector<double> v_2 = {2,3};

    ASSERT_EQ(dot_productV( &v_1, &v_2), -1);
    ASSERT_EQ(dot_productV( &v_2, &v_1), dot_productV( &v_1, &v_2));

    v_1 = {};
    v_2 = {};

    ASSERT_EQ(dot_productV( &v_1, &v_2), -1);
    ASSERT_EQ(dot_productV( &v_2, &v_1), dot_productV( &v_1, &v_2));

    v_1 = {1,2,3,4,5,6,7,8,9,0};
    v_2 = {0,9,8,7,6,5,4,3,2,1};

    ASSERT_EQ(dot_productV( &v_1, &v_2), 200);
    ASSERT_EQ(dot_productV( &v_2, &v_1), dot_productV( &v_1, &v_2));

    v_1 = {6,7,8,9,0};
    v_2 = {5,4,3,2,1};

    ASSERT_EQ(dot_productV( &v_1, &v_2), 100);
    ASSERT_EQ(dot_productV( &v_2, &v_1), dot_productV( &v_1, &v_2));
}

TEST(dot_product_test, unexpected_args){
    ASSERT_EQ( dot_product(new Matrix(2,2), new Matrix(3,3)), -1 );
    ASSERT_EQ( dot_product(new Matrix(2,1), new Matrix(3,3)), -1 );

    ASSERT_EQ( dot_product(new Matrix(2,2), new Matrix(3,1)), -1 );
    ASSERT_EQ(dot_product(new Matrix(2,1), new Matrix(3,1)), -1);

    ASSERT_EQ(dot_product(new Matrix(2,1), new Matrix(2,1)), 0);
    ASSERT_EQ(dot_product(new Matrix(2,1), new Matrix(2,2)), -1);

    ASSERT_EQ(dot_product(new Matrix(2,1), new Matrix(1,2)), 0);
    ASSERT_EQ(dot_product(new Matrix(10,1, {1,2,3,4,5,6,7,8,9,0}), new Matrix(1,10, {0,9,8,7,6,5,4,3,2,1})), 200);

    ASSERT_EQ(dot_product(new Matrix(1,10, {1,2,3,4,5,6,7,8,9,0}), new Matrix(1,10, {0,9,8,7,6,5,4,3,2,1})), 200);
    ASSERT_EQ(dot_product(new Matrix(5,1, {6,7,8,9,0}), new Matrix(1,5, {5,4,3,2,1})), 100);
}

TEST(orthogonal_test, unexpected_args){
    std::vector<double> v_1 = {};
    std::vector<double> v_2 = {};

    ASSERT_EQ(orthogonal( &v_1, &v_2), -1);
    ASSERT_EQ(orthogonal( &v_1, &v_2), orthogonal( &v_2, &v_1));

    v_1 = {1,2};
    v_2 = {2,-1};

    ASSERT_EQ(orthogonal( &v_1, &v_2), 1);
    ASSERT_EQ(orthogonal( &v_1, &v_2), orthogonal( &v_2, &v_1));

    v_1 = {1,2,8,9};
    v_2 = {4,3,2,1};

    ASSERT_EQ(orthogonal( &v_1, &v_2), 0);
    ASSERT_EQ(orthogonal( &v_1, &v_2), orthogonal( &v_2, &v_1));
}

TEST(norm_test, unexpected_args){

    Matrix v_1 = Matrix(2,1, {10, 9});
    ASSERT_EQ(norm(&v_1), std::sqrt(181));

    v_1 = Matrix(2,1);
    ASSERT_EQ(norm(&v_1), 0);

    v_1 = Matrix(3,3);
    ASSERT_DEATH(norm(&v_1), "");

    v_1 = Matrix(3,1, {2,3,5});
    Matrix v_2 = Matrix(1, 3, {2,3,5});

    ASSERT_EQ(norm(&v_1), norm(&v_2));
    ASSERT_EQ(norm(&v_1), std::sqrt(38));

    v_1 = Matrix(6,1, {9,8,7,6,5,4});
    v_2 = Matrix(1,6, {9,8,7,6,5,4});

    ASSERT_EQ(norm(&v_1), norm(&v_2));
    ASSERT_EQ(norm(&v_1), std::sqrt(271));
}

TEST(collinear_m_test, unexpected_args){
    Matrix m_1 = Matrix(2,1);
    Matrix m_2 = Matrix(2,1);

    ASSERT_FALSE(collinear_m(&m_1, &m_2));

    m_1 = Matrix(3,1);
    m_2 = Matrix(3,4);

    ASSERT_EQ(collinear_m(&m_1, &m_2), -1);
    m_2 = Matrix(1,3);

    ASSERT_EQ(collinear_m(&m_1, &m_2), -1);
    ASSERT_EQ(collinear_m(&m_2, &m_1), -1);

    m_1 = Matrix(3,1, {3,2,1});
    m_2 = Matrix(3,1, {9,6,3});

    ASSERT_EQ(collinear_m(&m_1, &m_2), collinear_m(&m_2, &m_1));
    ASSERT_TRUE(collinear_m(&m_1, &m_2));
}

TEST(collinear_v, unexpected_args){
    std::vector<double> v_1 = {1,2,3,4,5,6};
    std::vector<double > v_2 = {2,4,6,8,10,12};

    ASSERT_TRUE(collinear_v(&v_1, &v_2));
    ASSERT_EQ(collinear_v(&v_1, &v_2), collinear_v(&v_2, &v_1));

    v_1 = {1,2,3,4,5};
    v_2 = {5,4,3,2,1};

    ASSERT_FALSE(collinear_v(&v_1, &v_2));
    ASSERT_EQ(collinear_v(&v_1, &v_2), collinear_v(&v_2, &v_1));

    v_1 = {};
    v_2 = {};

    ASSERT_EQ(collinear_v(&v_1, &v_2), -1);
    ASSERT_EQ(collinear_v(&v_1, &v_2), collinear_v(&v_2, &v_1));
}

TEST(orthogonal_test_m, unexpected_args){
    std::vector<double> v_1 = {};
    std::vector<double> v_2 = {};

    ASSERT_EQ(orthogonal( &v_1, &v_2), -1);
    ASSERT_EQ(orthogonal( &v_1, &v_2), orthogonal( &v_2, &v_1));

    v_1 = {1,2};
    v_2 = {2,-1};

    ASSERT_EQ(orthogonal( &v_1, &v_2), 1);
    ASSERT_EQ(orthogonal( &v_1, &v_2), orthogonal( &v_2, &v_1));

    v_1 = {1,2,8,9};
    v_2 = {4,3,2,1};

    ASSERT_EQ(orthogonal( &v_1, &v_2), 0);
    ASSERT_EQ(orthogonal( &v_1, &v_2), orthogonal( &v_2, &v_1));
}

TEST(orthogonal_m_test, unexpected_args){
    Matrix m_1 = Matrix(2,1);
    Matrix m_2 = Matrix(1,2);

    ASSERT_EQ(collinear_m(&m_1, &m_2), -1);

    m_2 = Matrix(2,1);
    ASSERT_FALSE(collinear_m(&m_1, &m_2));

    m_1 = Matrix(3,1, {1,2,3});
    m_2 = Matrix(3,1, {10,20,30});

    ASSERT_TRUE(collinear_m( &m_1, &m_2 ));
    ASSERT_TRUE(collinear_m( &m_2, &m_1 ));
}