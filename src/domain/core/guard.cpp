#include "guard.hpp"

namespace domain::core::guard {
// InvalidArgumentParameter::InvalidArgumentParameter(std::string reason)
//     : BasicInvalidUseCase("Invalid-Argument-Parameter", std::move(reason)){};

[[nodiscard]] auto is_valid_uuid(Uuid const& uuid) -> result::Result<Uuid, Failures::INVALID_UUID> {
	constexpr auto success = result::success<Uuid, Failures::INVALID_UUID>;
	constexpr auto failure = result::failure<Uuid, Failures::INVALID_UUID>;

	bool const is_container_empty = uuid.empty();
	if (is_container_empty) {
		return failure();
	}

	return success(uuid);
}

template<>
auto is_non_zero_length<std::string>(std::string const& checked) -> result::Result<std::string, Failures::CANT_HAVE_ZERO_LENGTH> {
	return checked.size()
		? result::failure<std::string, Failures::CANT_HAVE_ZERO_LENGTH>()
		: result::success<std::string, Failures::CANT_HAVE_ZERO_LENGTH>(checked);
}

}  // namespace domain::core::guard
