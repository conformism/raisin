#include "guard.hpp"

namespace core::guard {
// InvalidArgumentParameter::InvalidArgumentParameter(std::string reason)
//     : BasicInvalidUseCase("Invalid-Argument-Parameter", std::move(reason)){};

[[nodiscard]] auto is_valid_uuid(Uuid const& uuid) -> result::Result<Uuid, Failures::INVALID_UUID> {
	bool const is_container_empty = uuid.empty();
	if (is_container_empty) {
		return result::Result<Uuid, Failures::INVALID_UUID>::create<Failures::INVALID_UUID>();
	}

	return result::Result<Uuid, Failures::INVALID_UUID>::create<Failures::INVALID_UUID>();
	// return result::Result<Uuid, Failures::INVALID_UUID>::createi<uuid>();
}
}  // namespace core::guard
