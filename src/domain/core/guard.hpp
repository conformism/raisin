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
[[nodiscard]] inline auto is_null_pointer(Ptr* pointer) -> result::
	Result<result::Success<Ptr*>, result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> {
	bool const is_valid_ptr = (pointer != nullptr);
	if (is_valid_ptr) {
		return result::Result<
			result::Success<Ptr*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::Success<Ptr*>{pointer});
	}
	return result::
		Result<result::Success<Ptr*>, result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>::create());
}

[[nodiscard]] auto is_valid_uuid(Uuid const& uuid) -> result::
	Result<result::Success<Uuid>, result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>;

}  // namespace core::guard
