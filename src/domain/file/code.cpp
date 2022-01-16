#include "code.hpp"

#include <utility>

namespace domain::file {

Code::Code(
  Uuid file,
  uint64_t start_line,
  uint64_t end_line,
  uint64_t start_char,
  uint64_t end_char
) :
  _file(std::move(file)),
  _start_line(start_line),
  _end_line(end_line),
  _start_char(start_char),
  _end_char(end_char)
{};

auto Code::operator==(Code const& right) const -> bool {
	return
	  _file == right.get_file()
	  && _start_line == right.get_start_line()
	  && _end_line == right.get_end_line()
	  && _start_char == right.get_start_char()
	  && _end_char == right.get_end_char();
};

auto Code::operator!=(Code const& right) const -> bool {
	return !(*this == right);
};

auto Code::get_file() const -> Uuid {
	return _file;
};
auto Code::get_start_line() const -> uint64_t {
	return _start_line;
};
auto Code::get_end_line() const -> uint64_t {
	return _end_line;
};
auto Code::get_start_char() const -> uint64_t {
	return _start_char;
};
auto Code::get_end_char() const -> uint64_t {
	return _end_char;
};

} // namespace domain::file
