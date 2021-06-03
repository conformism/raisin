#include "guard.hpp"
#include <string>
#include <utility>

namespace core::guard {

InvalidArgumentParameter::InvalidArgumentParameter(
  std::string name,
  std::string reason
) :
  _name(std::move(name)),
  _reason(std::move(reason))
{}
} // namespace core::guard
