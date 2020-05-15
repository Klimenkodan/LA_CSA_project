cmake_minimum_required(VERSION 3.15)
project(LA_CSA_project)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(LA_CSA_project
        main.cpp
        wrapper_class/matrix.cpp
        src/matrix_operations.cpp
        helper_functions/helper_functions.cpp
        headers/matrix.h
        headers/matrix_operations.h
        helper_functions/helper_functions.h
        src/vector_operations.cpp
        headers/vector_operations.h
        tests/test_matrix.cpp
        tests/test_matrix_operations.cpp
        tests/test_vector_operations.cpp
        )

target_link_libraries(LA_CSA_project ${GTEST_LIBRARIES} pthread)