#include "../headers/helper_functions.h"
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>

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

// Helper function for read_matrix_conf
// Splits str by delimeter char
std::vector<std::string> split(const std::string strToSplit, char delimeter)
{
	std::stringstream ss(strToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (std::getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}


Matrix* read_matrix_conf(int m, int n, const char* file_name) {
	std::ifstream file(file_name);
	auto filev = read_file_into_memory(file);
	std::vector<std::string> rows;
	int r = 0;
	rows.emplace_back("");
	for (auto c: filev) {
		if (c == '\n') {
			r++;
			rows.emplace_back("");
		}
		else {
			rows[r] += c;
		}
	}
	auto* res = new Matrix(m, n);
	int x = 0;
	for (auto str: rows) {
		int y = 0;
		auto splitted = split(str, ' ');
		for (auto snum: splitted) {
			res->set_element(x, y, std::stod(snum));
			y++;
		}
		x++;
	}
	return res;
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

