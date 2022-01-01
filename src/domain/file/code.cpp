#include "code.hpp"

namespace domain::file {

Code::Code(
  File const* file,
  int start_line,
  int end_line,
  std::optional<int> start_char = std::nullopt,
  std::optional<int> end_char = std::nullopt
) :
  _file(file),
  _start_line(start_line),
  _end_line(end_line),
  _start_char(start_char),
  _end_char(end_char)
{};

} // namespace domain::file
