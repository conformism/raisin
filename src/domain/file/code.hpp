#pragma once

#include "domain/file/file.hpp"
#include <optional>

namespace domain::file {

class Code {
public:
	Code(
	  File const* file,
	  int start_line,
	  int end_line,
	  std::optional<int> start_char,
	  std::optional<int> end_char);
private:
	File const* _file;
	int const _start_line;
	int const _end_line;
	std::optional<int> const _start_char;
	std::optional<int> const _end_char;
};

} // namespace domain::file
