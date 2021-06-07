#include "guard.hpp"

#include "result.hpp"
#include <memory>
#include <string>
#include <utility>
#include <any>

namespace core::guard {

auto against_zero_lenght(
	std::string const* string_to_check,
	std::string const* string_name
) -> std::unique_ptr<result::Result<std::string>> {
	if(string_to_check->empty()) {
		return result::ResultFactory<std::string>::createBasicDomainResultSuccess(string_to_check);
	}

	std::string const reason = "The string" + *string_name + "is empty.";


	InvalidArgumentParameter const* invalid_use_case = new InvalidArgumentParameter(
		reason
	);
	return result::ResultFactory<std::string>
	  ::createBasicDomainResultError(invalid_use_case);
}

} // namespace core::guard
