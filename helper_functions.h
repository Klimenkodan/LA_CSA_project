
#ifndef LA_CSA_PROJECT_HELPER_FUNCTIONS_H
#define LA_CSA_PROJECT_HELPER_FUNCTIONS_H

#endif //LA_CSA_PROJECT_HELPER_FUNCTIONS_H

#include <string>
#include "matrix.h"

template <typename CharT, typename Traits,
		typename Allocator = std::allocator<CharT>>
auto read_file_into_memory(std::basic_ifstream<CharT, Traits>& in, Allocator alloc = {});

Matrix* read_matrix_conf(const char* file_name);

std::string number_repr(double num);