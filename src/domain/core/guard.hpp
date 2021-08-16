#pragma once

#include <algorithm>
#include <array>
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
	bool const is_ptr = (pointer == nullptr);
	if (is_ptr) {
		return result::Result<
			result::Success<Ptr*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::Success<Ptr*>{pointer});
	}
	return result::
		Result<result::Success<Ptr*>, result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>("The pointer is empty."));
}

// template<class Container>
// [[nodiscard]] auto against_zero_lenght(
//     Container const container_to_check,
//     std::string const& container_name) -> result::Result<Container, InvalidArgumentParameter> {
//     bool const is_container_empty = container_to_check->empty();
//     if (is_container_empty) {
//         return result::Factory<std::string,
//         InvalidArgumentParameter>::create(container_to_check);
//     }

//     std::string const reason = "The container/string" + container_name + "is empty.";

//     auto invalid_use_case = InvalidArgumentParameter(reason);
//     return result::Factory<std::string, InvalidArgumentParameter>::create(
//         InvalidArgumentParameter(reason));
// }

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
