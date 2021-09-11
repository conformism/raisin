#include "guard.hpp"

namespace core::guard {
// InvalidArgumentParameter::InvalidArgumentParameter(std::string reason)
//     : BasicInvalidUseCase("Invalid-Argument-Parameter", std::move(reason)){};

[[nodiscard]] auto is_valid_uuid(Uuid const& uuid) -> result::
	Result<result::Success<Uuid>, result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> {
	bool const is_container_empty = uuid.empty();
	if (is_container_empty) {
		return result::Result<
			result::Success<Uuid>,
			result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
			result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>(
				BasicFailureRegistrar::INVALID_UUID));
	}

	return result::
		Result<result::Success<Uuid>, result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
			result::Success<Uuid>{uuid});
}
}  // namespace core::guard
