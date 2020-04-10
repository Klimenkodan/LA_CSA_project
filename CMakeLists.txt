cmake_minimum_required(VERSION 3.15)
project(LA_CSA_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(LA_CSA_project main.cpp wrapper_class/matrix.cpp src/matrix_operations.cpp helper_functions/helper_functions.cpp headers/matrix.h headers/matrix_operations.h headers/helper_functions.h src/vector_operations.cpp headers/vector_operations.h)