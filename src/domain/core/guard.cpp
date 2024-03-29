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
}  // namespace domain::core::guard
