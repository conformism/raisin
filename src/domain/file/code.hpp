#pragma once

#include "domain/core/types.hpp"
#include "domain/file/file.hpp"
#include <functional>
#include <optional>

namespace domain::file {

class Code : public core::Value<Code> {
public:
	Code(
	  Uuid file,
	  int start_line,
	  int end_line,
	  int start_char,
	  int end_char);
	auto operator==(Code const& right) const -> bool override;

	Uuid file;
	int start_line;
	int end_line;
	int start_char;
	int end_char;
};

} // namespace domain::file
