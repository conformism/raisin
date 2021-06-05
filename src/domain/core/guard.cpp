#include "guard.hpp"

#include "result.hpp"
#include <memory>
#include <string>
#include <utility>
#include <any>

namespace core::guard {

auto against_zero_lenght(
	std::string const* string_to_check,
	std::string const& string_name
) -> std::unique_ptr<result::Result<bool>> {
	if(string_to_check->empty()) {
		return result::ResultFactory<bool>
			  ::createBasicDomainResultSuccess(true);
	}
	std::string reason = {"The string", std::allocator<char>()};
	reason.append(string_name);
	reason.append(" is empty.");

	const result::InvalidUseCaseTypes*
	invalid_use_case = new InvalidArgumentParameter(
		reason
	);
	return result::ResultFactory<bool>
	  ::createBasicDomainResultError(invalid_use_case);
}

} // namespace core::guard
