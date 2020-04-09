#include "helper_functions.h"
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <cstring>
#define ERROR 0.000001

template <typename CharT, typename Traits,
		typename Allocator>
auto read_file_into_memory(std::basic_ifstream<CharT, Traits>& in, Allocator alloc)
{
	using std::begin;
	using std::end;

	auto const chunk_size = std::size_t{BUFSIZ};

	auto container = std::vector<CharT, Allocator>(
			std::move(alloc));

	auto chunk = std::array<char, chunk_size>{};

	while (
			in.read(chunk.data(), chunk.size()) ||
			in.gcount())
		container.insert(end(container),
		                 begin(chunk),
		                 begin(chunk) + in.gcount());
	return container;
}

Matrix* read_matrix_conf(const char* file_name) {
	std::ifstream file(file_name);
	auto filev = read_file_into_memory(file);
	std::vector<double> res;
	const char* temp = "";
	char * end;
	size_t height = 0;
	size_t width = 0;
	for (auto c: filev) {
		if (c == '\n') {
			++height;
			res.emplace_back(strtod(temp, &end));
			temp = "";
		}

		else if (c == ' ') {
			res.emplace_back(strtod(temp, &end));
			temp = "";
		}

		else {
			temp += c;
		}
	}
	if (strcmp(temp, "") != 0) {
		res.emplace_back(strtod(temp, &end));
	}

	std::cout << height << std::endl;
	width = res.size() / height;

	auto* matrix = new Matrix(height, width);
	for (size_t i=0; i < height; i++) {
		for (size_t j=0; j < width; j++) {
			matrix->set_element(i, j, res[i * width + j]);
		}
	}
	return matrix;
}


std::string number_repr(double num) {
	if (std::abs(static_cast<int>(num) - num) < ERROR) {

		return std::to_string(static_cast<int>(num));
	}

	else {
		return std::to_string(num);
	}

}

bool check_valid(int row_num, int col_num, int width, int height) {
	return ( 0 <= row_num && row_num < height && 0 <= col_num  && col_num < width);
}