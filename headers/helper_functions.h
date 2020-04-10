#ifndef LA_CSA_PROJECT_HELPER_FUNCTIONS_H
#define LA_CSA_PROJECT_HELPER_FUNCTIONS_H

#endif //LA_CSA_PROJECT_HELPER_FUNCTIONS_H

#include <string>
#include "matrix.h"

template <typename CharT, typename Traits,
		typename Allocator = std::allocator<CharT>>
auto read_file_into_memory(std::basic_ifstream<CharT, Traits>& in, Allocator alloc = {});

std::string number_repr(double num);

bool check_valid(int row_num, int col_num, int weight, int height);

Matrix* read_matrix_conf(int m, int n, const char* file_name);