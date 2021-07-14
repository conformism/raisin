#pragma once

#include "result.hpp"
#include "types.hpp"

#include <array>
#include <string>
#include <utility>
#include <variant>

namespace core::guard {
class InvalidArgumentParameter: public result::InvalidUseCaseTypes {
public:
	explicit InvalidArgumentParameter(std::string reason);
	[[nodiscard]]
	auto get_name() const -> std::string override;
	[[nodiscard]]
	auto get_reason() const -> std::string override;
private:
	std::string const _name;
	std::string const _reason;
};

template<class Container>
[[nodiscard]]
auto againstZeroLenght(
	Container const* container_to_check,
	std::string const& container_name
) -> result::Result<Container, InvalidArgumentParameter> {
	bool const is_container_empty = container_to_check->empty();
	if(is_container_empty) {
		return result::Factory<std::string, InvalidArgumentParameter>::create(container_to_check);
	}

	std::string const reason = "The container/string" + container_name + "is empty.";

	auto invalid_use_case = InvalidArgumentParameter(
		reason
	);
	return result::Factory<std::string, InvalidArgumentParameter>::create(
		InvalidArgumentParameter(reason));
}

template<class Contained>
[[nodiscard]]
auto isOneOf(
	Uuid const& uuid,
	std::map<Uuid, Contained*>* collection,
	std::string const& collection_name
) -> result::Result<Contained, result::InvalidUseCaseTypes> {

	bool const contains_this_uuid = collection->count(uuid) > 0;
	if(contains_this_uuid) {
		Contained const* contained = collection->at(uuid);
		return result::Result<Contained, result::InvalidUseCaseTypes>::Factory
		  ::createBasicDomainResultSuccess(contained);
	}

	std::string reason = "No Contained at uuid: " + uuid + " is not present into collection: " + collection_name;
	reason.append(collection_name);

	return result::Result<Contained, result::InvalidUseCaseTypes>::Factory::create_error(
		InvalidArgumentParameter(reason));
}
} // namespace core::guard
