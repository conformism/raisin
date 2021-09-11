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
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>());
}

[[nodiscard]] auto is_valid_uuid(Uuid const& uuid) -> result::
	Result<result::Success<Uuid>, result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>;

// TODO(dauliac) Remove this guard, it's removed to be implemented into Agregate object
// template<typename Contained>
// [[nodiscard]] inline auto is_one_of(
//     Uuid const& uuid,
//     Aggregator<Contained> const* collection
// ) -> result::
//     Result<result::Success<Contained*>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>>
//     { bool const is_contains_this_uuid = collection->count(uuid) > 0; if (is_contains_this_uuid)
//     {
//         return result::Result<
//             result::Success<Contained*>,
//             result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>>(result::Success<Contained*>{collection->at(uuid)});
//     }

//     std::string reason =
//         "No Contained at uuid: " + uuid + " is not present into collection.";

//     auto const failure = result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>(reason);
//     return result::Result<
//         result::Success<Contained*>,
//         result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>>(failure);
// }
}  // namespace core::guard
