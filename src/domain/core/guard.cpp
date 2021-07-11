#include "guard.hpp"

namespace core::guard {
 InvalidArgumentParameter::InvalidArgumentParameter(std::string reason) :
	_name(
		"Invalid-Argument-Parameter",
		std::allocator<char>()
	),
	_reason(std::move(reason))
{};
auto InvalidArgumentParameter::get_name() const -> std::string {
	return _name;
};
auto InvalidArgumentParameter::get_reason() const -> std::string {
	return _reason;
};

} // namespace core::guard
