cmake_minimum_required(VERSION 3.15)
project(LA_CSA_project)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)

add_executable(LA_CSA_project main.cpp headers/ctpl.h wrapper_class/matrix.cpp src/matrix_operations.cpp helper_functions/helper_functions.cpp headers/matrix.h headers/matrix_operations.h helper_functions/helper_functions.h src/vector_operations.cpp headers/vector_operations.h tests/test_matrix.cpp tests/test_matrix.h tests/test_matrix_operations.cpp tests/test_matrix_operations.h src/parallel_matrix_operations.cpp src/parallel_vector_operations.cpp headers/parallel_matrix_operations.h headers/parallel_vector_operations.h)

target_link_libraries(LA_CSA_project Threads::Threads)