cmake_minimum_required(VERSION 3.15)
project(LA_CSA_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(LA_CSA_project main.cpp matrix.cpp matrix_operations.cpp helper_functions.cpp matrix.h matrix_operations.h helper_functions.h vector_operations.cpp vector_operations.h)