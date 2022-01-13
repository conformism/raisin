#include "code.hpp"

#include <utility>

namespace domain::file {

Code::Code(
  Uuid file,
  int start_line,
  int end_line,
  int start_char,
  int end_char
) :
  file(std::move(file)),
  start_line(start_line),
  end_line(end_line),
  start_char(start_char),
  end_char(end_char)
{};

auto Code::operator==(Code const& right) const -> bool {
	return file == right.file
	  && start_line == right.start_line
	  && end_line == right.end_line
	  && start_char == right.start_char
	  && end_char == right.end_char;
};

} // namespace domain::file
