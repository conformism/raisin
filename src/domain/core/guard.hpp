#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

#include "result.hpp"
#include "types.hpp"

namespace domain::core {
template<class T>
class Aggregator;
}  // namespace domain::core

namespace domain::core::guard {

template<typename Ptr>
[[nodiscard]] inline auto is_null_pointer(Ptr* pointer)
	-> result::Result<Ptr*, Failures::NO_RESOURCES> {
	constexpr auto success = result::success<Ptr*, Failures::NO_RESOURCES>;
	constexpr auto failure = result::failure<Ptr*, Failures::NO_RESOURCES>;

	bool const is_valid_ptr = (pointer != nullptr);
	if (is_valid_ptr) {
		// return result::Result<Ptr*, Failures::NO_RESOURCES>::createi<pointer>();
		return success(pointer);
	}
	return failure();
}

[[nodiscard]] auto is_valid_uuid(Uuid const& uuid) -> result::Result<Uuid, Failures::INVALID_UUID>;

template<typename T>
[[nodiscard]] auto is_non_zero_length(T const& checked) -> result::Result<T, Failures::CANT_HAVE_ZERO_LENGTH>;

}  // namespace domain::core::guard
