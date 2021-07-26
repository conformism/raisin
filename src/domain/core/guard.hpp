#pragma once

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <utility>
#include <variant>

#include "result.hpp"
#include "types.hpp"

namespace core::guard {

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

template<typename Contained>
[[nodiscard]] auto is_one_of(
	Uuid const& uuid,
	Compositor<Contained> const* collection,
	std::string const& collection_name) -> result::
	Result<result::Success<Contained*>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> {
	bool const contains_this_uuid = collection->count(uuid) > 0;
	if (contains_this_uuid) {
		auto const success = result::Success<Contained*>{collection->at(uuid).get()};
		return result::Result<
			result::Success<Contained*>,
			result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>>(success);
	}

	std::string reason =
		"No Contained at uuid: " + uuid + " is not present into collection: " + collection_name;

	auto const failure = result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>(reason);
	return result::Result<
		result::Success<Contained*>,
		result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>>(failure);
}
}  // namespace core::guard
