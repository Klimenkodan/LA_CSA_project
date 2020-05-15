#include "../headers/matrix_operations.h"
#include "../helper_functions/helper_functions.h"
#include "../headers/vector_operations.h"
#include <gtest/gtest.h>
//
//TEST(sizes_equal_test, unexpected_args){
//    Matrix m_1 = Matrix(5,4);
//    Matrix m_2 = Matrix(5,4);
//
//    ASSERT_TRUE(sizes_equal( &m_1,  &m_2 ));
//    ASSERT_FALSE(sizes_equal( new Matrix(5,4),  new Matrix(4,5) ));
//
//    ASSERT_TRUE( sizes_equal( new Matrix(1,1),  new Matrix(1,1) ) );
//    ASSERT_TRUE( sizes_equal( new Matrix(1,1, {2}),  new Matrix(1,1, {3}) ) );
//
//    ASSERT_TRUE( sizes_equal( new Matrix(1,1),  new Matrix(1,1, {5} ) ) );
//    ASSERT_TRUE( sizes_equal( new Matrix(2,3),  new Matrix(2,3, {1,1,2,3,4,5} ) ) );
//
//    ASSERT_DEATH( sizes_equal( new Matrix(0,2),  new Matrix(2,0, {1,1} ) ), "" );
//    ASSERT_FALSE( sizes_equal( new Matrix(3,2),  new Matrix(2,3, {1,1,2,3,4,5} ) ) );
//
//    m_1.add_column( new Matrix(5, 1, {1,1,1,1,1}),0 );
//    m_1.add_column( new Matrix(5, 1, {1,1,1,1,1}),3 );
//    m_2.add_to_row(1,2,3);
//    m_2.multiply_row(0, -5);
//
//    ASSERT_TRUE(sizes_equal( &m_1,  &m_2 ) );
//    m_1.interchange_rows(0,2);
//
//    ASSERT_TRUE( sizes_equal( &m_1,  &m_2 ) );
//}
//
//TEST(add_matrix_test, unexpected_args){
//    Matrix m_1 = Matrix(4,2, {1,1,1,1,1,1,1, 1});
//    Matrix m_2 = Matrix(4,2,{2,2,2,2,2,2,2,2});
//    Matrix m_4 = Matrix(4,2, {3,3,3,3,3,3,3,3});
//
//    auto m_3 = add_matrix(&m_1, &m_2, 1, 1);
//    for(int i = 0; i < m_1.get_width(); ++i){
//        for(int j = 0; j < m_1.get_height(); ++j){
//            ASSERT_EQ( m_4.get_element(j, i), m_3->get_element(j,i) );
//        }
//    }
//
//    m_1 = Matrix(2,4);
//    ASSERT_DEATH( add_matrix(&m_1, &m_2, 1, 1), "");
//    ASSERT_DEATH(add_matrix(&m_2, &m_1, 1, 1), "");
//
//    m_1 = Matrix(2,3, {1,2,3,4,5,6});
//    m_2 = Matrix(2,3);
//
//    m_4 = Matrix(2, 3, {2,4,6,8,10,12});
//    m_3 = add_matrix(&m_1, &m_2, 2, 3);
//
//    for(int i = 0; i < m_1.get_width(); ++i){
//        for(int j = 0; j < m_1.get_height(); ++j){
//            ASSERT_EQ( m_4.get_element(j, i), m_3->get_element(j,i) );
//        }
//    }
//
//    m_1 = Matrix(5,5);
//    m_2 = Matrix(5,5);
//    m_3 = add_matrix(&m_1, &m_2, 5, 10);
//
//    for(int i = 0; i < m_1.get_width(); ++i){
//        for(int j = 0; j < m_1.get_height(); ++j){
//            ASSERT_EQ( m_3->get_element(j, i), 0 );
//        }
//    }
//}
//
//TEST(multiply_matrix_test, unexpected_args) {
//    Matrix m_1 = Matrix(2, 2, {3, 4, 5, 6});
//    Matrix m_2 = Matrix(2, 5, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
//
//    auto m_3 = multiply_matrix(&m_1, &m_2);
//    ASSERT_EQ(multiply_matrix(&m_2, &m_1), nullptr);
//
//    ASSERT_EQ(m_3->get_height(), 2);
//    ASSERT_EQ(m_3->get_width(), 5);
//
//    m_3 = new Matrix(2, 5, {27, 34, 41, 48, 55, 41, 52, 63, 74, 85});
//    ASSERT_TRUE(m_3->equal(new Matrix(2, 5, {27, 34, 41, 48, 55, 41, 52, 63, 74, 85}), 0.0001));
//}
//
//TEST(identity_matrix_test, unexpected_args){
//    auto m_1 = identity(5);
//    int ones = 0;
//
//    ASSERT_EQ(m_1->get_width(), m_1->get_height());
//
//    for (int i = 0; i < m_1->get_width(); i++){
//        for (int j = 0; j < m_1->get_height(); j++){
//            if (m_1->get_element(i, j) != 0) {
//                ASSERT_EQ(i, j);
//                ones++;
//            }
//        }
//    }
//    ASSERT_EQ(m_1->get_width(), ones);
//}
//
//TEST(scalar_multiply_test, unexpected_args){
//    int sc = 0;
//    Matrix m_1 = Matrix(2,3, {4,3,2,1,0,-1});
//    auto m_2 = scalar_multiply(&m_1, sc);
//
//    for (int i = 0; i < m_1.get_height(); ++i ){
//        for (int j = 0; j < m_1.get_width(); ++j) {
//            ASSERT_EQ(m_2->get_element(i, j), m_1.get_element(i, j) * sc );
//        }
//    }
//}
//
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
//    for (int i = 0; i < m_1.get_height() - 1; i++){
//        for (int j = i + 1; j < m_1.get_height(); ++j) {
//            ASSERT_EQ( m_1.get_element(j, i), 0 );
//        }
//    }
//
//}
//
//TEST(rref_test, unexpected_args){
//    Matrix m_1 = Matrix( 6,3, {5,6,7,1,3,7,10,11,16,17,21,23,29,8,3,0,1,2} );
//    m_1 = *rref(&m_1);
//
//    Matrix m_2 = Matrix(3, 6, {5,6,7,1,3,7,10,11,16,17,21,23,29,8,3,0,1,2});
//    m_2 = *rref(&m_2);
//
//    for (int i = 0; i < 3; ++i){
//        int sum_1 = 0;
//        for(int j = 0; j < m_1.get_height(); ++j){
//            sum_1 += m_1.get_element(j, i);
//        }
//       ASSERT_EQ(sum_1, 1);
//    }
//
//    for (int i = 0; i < 3; ++i){
//        int sum_2 = 0;
//        for(int j = 0; j < m_2.get_height(); ++j){
//            sum_2 += m_2.get_element(j, i);
//        }
//        ASSERT_EQ(sum_2, 1);
//    }
//
//    Matrix m_3 = Matrix(4,4, {5,6,7,1,3,7,10,11,16,17,21,23,29,8,3,0});
//    m_3 = *rref(&m_3);
//
//    for (int i = 0; i < m_3.get_width(); ++i){
//        int sum = 0;
//        for(int j = 0; j < m_3.get_height(); ++j){
//            sum += m_3.get_element(j, i);
//        }
//    }
//}
//
TEST(inverse_test, unexpected_args){
    Matrix m_1 = Matrix( 4,4, {5,6,7,1,3,7,10,11,16,17,21,23,29,8,3,0} );
    auto m_2 = inverse(&m_1);

    ASSERT_TRUE( identity(4)->equal( multiply_matrix(&m_1, m_2), 1 ) );
    ASSERT_EQ(inverse( new Matrix(5,5) ), nullptr );

    m_1 = Matrix( 3,3, {-5,0,-1,1,2,-1,-3,4,1} );
    m_2 = inverse(&m_1);

    ASSERT_TRUE( identity(3)->equal( multiply_matrix(&m_1, m_2), 1 ) );

    m_1 = Matrix( 3,3, {0,0,3,0,5,0,0,0,4} );
    ASSERT_EQ(inverse(&m_1), nullptr);

    m_1 = Matrix(3,2, {1,2,3,4,5,6});
    ASSERT_DEATH(inverse(&m_1), "");

    m_1 = Matrix(2,2, {1,2,3,4});
    m_2 = inverse(&m_1);
    ASSERT_TRUE( identity(2)->equal( multiply_matrix(&m_1, m_2), 1 ) );
}
//
//TEST(rank_test, unexpected_args){
//    Matrix m_1 = Matrix(3,2, {1,2,3,4,5,6});;
//    ASSERT_EQ(2, rank(&m_1));
//
//    Matrix m_2 = Matrix( 4,4, {5,6,7,1,3,7,10,11,16,17,21,23,29,8,3,0} );
//    ASSERT_EQ(4, rank(&m_2));
//
//    Matrix m_3 = Matrix(3,4, {1,1,-3,5,0,1,-1,15,0,0,1,12});
//    ASSERT_EQ(3, rank(&m_3));
//
//    Matrix m_4 = Matrix(3,4);
//    ASSERT_EQ(0, rank(&m_4));
//}
//
//TEST(solution_test, unexpected_args){}
//
//TEST(transpose_test, unexpected_args){
//
//    Matrix m_1 = Matrix(3,2,{1,2,3,4,5,6});
//    Matrix m_2 = *transpose(&m_1);
//
//    ASSERT_TRUE(m_2.equal(new Matrix(2,3,{1,3,5,2,4,6}), 0.01));
//
//    m_1 = Matrix(3,3,{1,2,3,4,5,6,9,8,7});
//    m_2 = *transpose(&m_1);
//
//    ASSERT_TRUE(m_2.equal(new Matrix(3,3,{1,4,9,2,5,8,3,6,7}), 0.01));
//}
//
//TEST(determinant_test, unexpected_args){
//    Matrix m_1 = Matrix( 4,4, {5,6,7,1,3,7,10,11,16,17,21,23,29,8,3,0} );
//    double expected_det = -614;
//
//    bool b = expected_det == determinant(&m_1);
//
//    ASSERT_TRUE( expected_det== determinant(&m_1) );
//    ASSERT_EQ(determinant(new Matrix(2,3)), -1);
//
//    m_1 = Matrix(2,2,{1,2,3,4});
//    expected_det = -2;
//
//    ASSERT_EQ(expected_det, determinant(&m_1));
//    m_1 = Matrix( 3,3, {0,0,3,0,5,0,0,0,4} );
//
//    ASSERT_EQ(0, determinant(&m_1));
//    ASSERT_EQ(0, determinant( new Matrix(4,4)) );
//}
//
//TEST(trace_test, unexpected_args){
//    Matrix m_1 = Matrix( 4,4 );
//    ASSERT_EQ(0, trace(&m_1));
//
//    Matrix m_2 = Matrix(3,3, {1,2,3,4,5,6,7,9,8});
//    ASSERT_EQ(trace(&m_2), 14);
//
//    Matrix m_3 = Matrix(3,4);
//    ASSERT_EQ(-1, trace(&m_3));
//
//    Matrix m_4 = Matrix(2,2, {1,2,0,0});
//    ASSERT_EQ(1, trace(&m_4));
//}
//
//TEST(QR_factorization_test, unexpected_args){
//    Matrix m_1 = Matrix( 3,3, {1,2,3,4,5,6,7,8,9} );
//    auto res = QR_factorization(&m_1);
//
//    auto Q = res["Q"];
//    auto Q_in = inverse(Q);
//
//    auto Q_trasp = transpose(Q);
//    auto R = res["R"];
//
//    ASSERT_TRUE( identity(3)->equal(multiply_matrix(Q,Q_in), 0.1) );
//    ASSERT_TRUE( identity(3)->equal(multiply_matrix(Q_in,Q), 0.1) );
//    ASSERT_TRUE(is_upper(R));
//
//    m_1 = Matrix(5, 5, {
//            1, 2, 3, 4, 5,
//            6, 7, 8, 9, 0,
//            5, 4, 3, 2, 1,
//            2, 2, 5, 6, 0,
//            1, 5, 8, 2, 9
//    });
//
//    res = QR_factorization(&m_1);
//
//    Q = res["Q"];
//    Q_in = inverse(Q);
//
//    Q_trasp = transpose(Q);
//    R = res["R"];
//
//    ASSERT_TRUE( identity(5)->equal(multiply_matrix(Q,Q_in), 0.1) );
//    ASSERT_TRUE( identity(5)->equal(multiply_matrix(Q_in,Q), 0.1) );
//    ASSERT_TRUE(is_upper(R));
//
//   m_1 =  Matrix(3, 3, {
//            1, 2, 3,
//            6, 7, 8,
//            5, 4, 3
//    });
//
//    res = QR_factorization(&m_1);
//
//    Q = res["Q"];
//    Q_in = inverse(Q);
//
//    Q_trasp = transpose(Q);
//    R = res["R"];
//
//    ASSERT_TRUE( identity(3)->equal(multiply_matrix(Q,Q_in), 0.1) );
//    ASSERT_TRUE( identity(3)->equal(multiply_matrix(Q_in,Q), 0.1) );
//    ASSERT_TRUE(is_upper(R));
//
//    m_1 = Matrix(3, 3, {
//            1, 2, 5,
//            9, 4, 0,
//            0, 2, 0
//    });
//
//    res = QR_factorization(&m_1);
//
//    Q = res["Q"];
//    Q_in = inverse(Q);
//
//    Q_trasp = transpose(Q);
//    R = res["R"];
//
//    ASSERT_TRUE( identity(3)->equal(multiply_matrix(Q,Q_in), 0.1) );
//    ASSERT_TRUE( identity(3)->equal(multiply_matrix(Q_in,Q), 0.1) );
//    ASSERT_TRUE(is_upper(R));
//
//    m_1 = Matrix(3, 3, {
//            0, 2, 1,
//            9, 4, 0,
//            1, 2, 0
//    });
//
//    res = QR_factorization(&m_1);
//
//    Q = res["Q"];
//    Q_in = inverse(Q);
//
//    Q_trasp = transpose(Q);
//    R = res["R"];
//
//    ASSERT_TRUE( identity(3)->equal(multiply_matrix(Q,Q_in), 0.1) );
//    ASSERT_TRUE( identity(3)->equal(multiply_matrix(Q_in,Q), 0.1) );
//    ASSERT_TRUE(is_upper(R));
//}

//TEST(isUpper_test, validMatrix){
//    Matrix m_1 = Matrix(3,3, {4, 3, 2,
//                              0, 4,-1,
//                              0, 0, 4});
//
//    Matrix m_2 = Matrix(2, 2, {4, 3,
//                               0, 4});
//
//    Matrix m_4 = Matrix(2, 2, {0, 0,
//                               0, 0});
//
//    Matrix m_3 = Matrix(4,4, {4, 3, 2, 6,
//                              0, 4,-1, 8,
//                              0, 0,-1, 8,
//                              0, 0, 0, 4});
//
//    ASSERT_TRUE(is_upper(&m_1));
//    ASSERT_TRUE(is_upper(&m_2));
//    ASSERT_TRUE(is_upper(&m_3));
//    ASSERT_TRUE(is_upper(&m_4));
//}
//
//TEST(isUpper_test, invalidMatrix){
//    Matrix m_1 = Matrix(3,3, {4, 3, 2,
//                              0, 4,-1,
//                              0, 1, 4});
//
//    Matrix m_2 = Matrix(2, 2, {4, 3,
//                               1, 4});
//
//    Matrix m_3 = Matrix(4,4, {4, 3, 2, 6,
//                              1, 4,-1, 8,
//                              0, 0,-1, 8,
//                              0, 0, 0, 4});
//
//    Matrix m_4 = Matrix(3,2, {4, 3, 2,
//                              0, 4,-1});
//
//    Matrix m_5 = Matrix(1,6, {4, 3, 2,
//                              0, 4,-1});
//
//    ASSERT_FALSE(is_upper(&m_1));
//    ASSERT_FALSE(is_upper(&m_2));
//    ASSERT_FALSE(is_upper(&m_3));
//    ASSERT_FALSE(is_upper(&m_4));
//    ASSERT_FALSE(is_upper(&m_5));
//}
//
//TEST(traceTest, validCases){
//    Matrix m_1 = Matrix(3,3, {4, 3, 2,
//                              0, 4,-1,
//                              5, 0, 4});
//
//    Matrix m_2 = Matrix(2, 2, {4, 3,
//                               0, 4});
//
//    Matrix m_3 = Matrix(4,4, {0, 3, 2, 6,
//                              0, 0,-1, 8,
//                              0, 0, 0, 8,
//                              0, 4, 0, 0});
//
//    Matrix m_4 = Matrix(2, 2, {0, 0,
//                               0, 0});
//
//    Matrix m_5 = Matrix(1, 1, {1});
//
//    ASSERT_EQ(trace(&m_1), 12);
//    ASSERT_EQ(trace(&m_2), 8);
//    ASSERT_EQ(trace(&m_3), 0);
//    ASSERT_EQ(trace(&m_4), 0);
//    ASSERT_EQ(trace(&m_5), 1);
//}
//
//TEST(traceTest, invalidCases){
//    Matrix m_1 = Matrix(3,2, {4, 3, 2,
//                              5, 0, 4});
//
//    Matrix m_2 = Matrix(2, 6, {4, 3,
//                               0, 4, 0, 4, 0, 4, 0, 4, 0, 4});
//
//    Matrix m_3 = Matrix(4,5, {0, 3, 2, 6,
//                              0, 0,-1, 8,
//                              0, 0,-1, 8,
//                              0, 0, 0, 8,
//                              0, 4, 0, 0});
//
//    Matrix m_4 = Matrix(3, 2, {0, 0, 0, 0,
//                               0, 0});
//
//    ASSERT_EQ(trace(&m_1), -1);
//    ASSERT_EQ(trace(&m_2), -1);
//    ASSERT_EQ(trace(&m_3), -1);
//    ASSERT_EQ(trace(&m_4), -1);
//}
//
//TEST(eigenValuesTest, generalTest){
//    Matrix m_1 = Matrix(5, 5, {
//            1, 2, 3, 4, 5,
//            6, 7, 8, 9, 0,
//            5, 4, 3, 2, 1,
//            2, 2, 5, 6, 0,
//            1, 5, 8, 2, 9
//    });
//    //inf loop
//    std::vector<double> res_1 = {1.923, 6.011, 19.150};
//
//    Matrix m_2 = Matrix(3, 3, {
//            1, 2, 3,
//            6, 7, 8,
//            5, 4, 3
//    });
//    //fail (far from true result)
//    std::vector<double> res_2 = {-2.13217, 13.13217};
//
//
//    Matrix m_3 = Matrix(2, 2, {
//            1, 2,
//            9, 4
//    });
//    //ok
//    std::vector<double> res_3 = {-2, 7};
//
//    Matrix m_4 = Matrix(3, 3, {
//            1, 2, 5,
//            9, 4, 0,
//            0, 2, 0
//    });
//    //inf loop
//    std::vector<double> res_4 = {8.100};
//
//    Matrix m_5 = Matrix(3, 3, {
//            0, 0, 0,
//            9, 4, 0,
//            0, 2, 0
//    });//bug (-nan)
//    std::vector<double> res_5 = {0, 4};
//
//    Matrix m_6 = Matrix(3, 3, {
//            0, 2, 1,
//            9, 4, 0,
//            1, 2, 0
//    });//almost bug (-0.999999 instead of -1)
//    std::vector<double> res_6 = {-2, -1, 7};
//
//    std::vector<Matrix> matrices = {m_1, m_2, m_3, m_4, m_5, m_6};
//    std::vector<std::vector<double>> resVectors = {res_1, res_2, res_3, res_4, res_4, res_5, res_6};
//
//    for (auto g = 0; g < matrices.size(); ++g)
//    {
//        std::vector<double> localRes = qr_method_eigenvalues(&matrices[g]);
//        sort(localRes.begin(), localRes.end());
//        ASSERT_EQ(localRes.size(), resVectors[g]);
//        for (auto i = 0; i < localRes.size(); ++i)
//        {
//            for (auto j = 0; j < resVectors.size(); ++j)
//            {
//                ASSERT_DOUBLE_EQ(localRes[j], resVectors[g][j]);
//            }
//        }
//    }
//}
//
//TEST(eigenVectors, generalTest){
//    Matrix m_1 = Matrix(3, 3, {
//            1, 0, 0,
//            9, 1, 0,
//            1, 2, 1});
//    std::vector<double> vals_1 = {1};
//    //notinv
//    Matrix vect_1 = Matrix(3, 1, {0, 0, 1});
//
//    Matrix m_2 = Matrix(3, 3, {
//            1, 0, 1,
//            1, 2, 1,
//            1, 1, 1});
//    std::vector<double> vals_2 = {0, 1, 3};
//    //notinv
//    Matrix vect_2 = Matrix(3, 3, {-1, 0, 1,
//                                  -1, 1, 0,
//                                  0.5, 1.5, 1});
//
//    Matrix m_3 = Matrix(3, 3, {
//            1, 0, 1,
//            1, 1, 1,
//            0, 1, 0
//    });
//    std::vector<double> vals_3 = {0, 2};
//    //notinv
//    Matrix vect_3 = Matrix(3, 2, {-1, 0, 1,
//                                  1, 2, 1});
//
//    std::vector<Matrix> mat = {m_1, m_2, m_3};
//    std::vector<std::vector<double>> val = {vals_1, vals_2, vals_3};
//    std::vector<Matrix> vect = {vect_1, vect_2, vect_3};
//
//    for(auto i = 0; i < mat.size(); ++i)
//    {
//        ASSERT_EQ(eigen_vectors(&mat[i], val[i]), vect[i]);
//    }
//}
//
