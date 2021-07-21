#pragma once

#include "result.hpp"
#include "types.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <utility>
#include <variant>

namespace core::guard {
class InvalidArgumentParameter : public result::BasicInvalidUseCase {
public:
	explicit InvalidArgumentParameter(std::string reason);
};

template<class Container>
[[nodiscard]] auto against_zero_lenght(
	Container const container_to_check,
	std::string const& container_name) -> result::Result<Container, InvalidArgumentParameter> {
	bool const is_container_empty = container_to_check->empty();
	if (is_container_empty) {
		return result::Factory<std::string, InvalidArgumentParameter>::create(container_to_check);
	}

	std::string const reason = "The container/string" + container_name + "is empty.";

	auto invalid_use_case = InvalidArgumentParameter(reason);
	return result::Factory<std::string, InvalidArgumentParameter>::create(
		InvalidArgumentParameter(reason));
}

template<typename Contained>
[[nodiscard]] auto is_one_of(
	Uuid const& uuid,
	Aggregator<Contained> const* collection,
	std::string const& collection_name)
	-> result::BasicDomainResult<std::weak_ptr<Contained>, InvalidArgumentParameter> {
	bool const contains_this_uuid = collection->count(uuid) > 0;
	if (contains_this_uuid) {
		return result::BasicDomainResult<std::weak_ptr<Contained>, InvalidArgumentParameter>(
			std::weak_ptr<Contained>(collection->at(uuid)));
	}

	std::string reason =
		"No Contained at uuid: " + uuid + " is not present into collection: " + collection_name;
	auto not_one_of = InvalidArgumentParameter(reason);

	return result::BasicDomainResult<std::weak_ptr<Contained>, InvalidArgumentParameter>(
		not_one_of);
}
}  // namespace core::guard
