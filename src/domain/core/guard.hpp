#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

#include "result.hpp"
#include "types.hpp"

namespace core {
template<class T>
class Aggregator;
}  // namespace core

namespace core::guard {

template<typename Ptr>
[[nodiscard]] inline auto is_null_pointer(Ptr* pointer)
	-> result::Result<Ptr*, Failures::NO_RESOURCES> {
	bool const is_valid_ptr = (pointer != nullptr);
	if (is_valid_ptr) {
		result::Result<Ptr*, Failures::NO_RESOURCES> const a =
			result::Result<Ptr*, Failures::NO_RESOURCES>::createi<pointer>();
		return result::Result<Ptr*, Failures::NO_RESOURCES>::createi<pointer>();
	}
	return result::Result<Ptr*, Failures::NO_RESOURCES>::create<Failures::NO_RESOURCES>();
}

[[nodiscard]] auto is_valid_uuid(Uuid const& uuid) -> result::Result<Uuid, Failures::INVALID_UUID>;

}  // namespace core::guard
