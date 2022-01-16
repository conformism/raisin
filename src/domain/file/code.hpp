#pragma once

#include "domain/core/types.hpp"
#include "domain/file/file.hpp"
#include <cstdint>
#include <functional>
#include <optional>

namespace domain::file {

class Code : public core::Value<Code> {
public:
	Code(
	  Uuid file,
	  uint64_t start_line,
	  uint64_t end_line,
	  uint64_t start_char,
	  uint64_t end_char);
	auto operator==(Code const& right) const -> bool override;
	auto operator!=(Code const& right) const -> bool override;

	[[nodiscard]]
	auto get_file() const -> Uuid;
	[[nodiscard]]
	auto get_start_line() const -> uint64_t;
	[[nodiscard]]
	auto get_end_line() const -> uint64_t;
	[[nodiscard]]
	auto get_start_char() const -> uint64_t;
	[[nodiscard]]
	auto get_end_char() const -> uint64_t;

private:
	Uuid _file;
	uint64_t _start_line;
	uint64_t _end_line;
	uint64_t _start_char;
	uint64_t _end_char;
};

} // namespace domain::file
