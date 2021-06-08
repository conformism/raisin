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
	explicit InvalidArgumentParameter(std::string reason) :
		_name(
			"Invalid-Argument-Parameter",
			std::allocator<char>()
		),
		_reason(std::move(reason))
	{}
	[[nodiscard]]
	auto get_name() const -> std::string override {
		return _name;
	}
	[[nodiscard]]
	auto get_reason() const -> std::string override {
		return _reason;
	}
private:
	std::string const _name;
	std::string const _reason;
};

template<class Container>
[[nodiscard]]
auto againstZeroLenght(
	Container const* container_to_check,
	std::string const& container_name
) -> std::unique_ptr<result::Result<Container>> {
	bool const is_container_empty = container_to_check->empty();
	if(is_container_empty) {
		return result::Factory<std::string>::create_basic_domain_result_success(container_to_check);
	}

	std::string const reason = "The container/string" + container_name + "is empty.";

	InvalidArgumentParameter const* invalid_use_case = new InvalidArgumentParameter(
		reason
	);
	return result::Factory<std::string>
	  ::create_basic_domain_result_error(invalid_use_case);
}

template<class Contained>
[[nodiscard]]
auto isOneOf(
	Uuid const& uuid,
	std::map<Uuid, Contained*>* collection,
	std::string const& collection_name
) -> std::unique_ptr<result::Result<Contained>> {

	bool const contains_this_uuid = collection->count(uuid) > 0;
	if(contains_this_uuid) {
		Contained const* contained = collection->at(uuid);
		return result::Result<Contained>::Factory
		  ::createBasicDomainResultSuccess(contained);
	}

	std::string reason = "No Contained at uuid: " + uuid + " is not present into collection: " + collection_name;
	reason.append(collection_name);

	InvalidArgumentParameter const* invalid_use_case = new InvalidArgumentParameter(
		reason
	);

	return result::Result<Contained>::Factory
	  ::createBasicDomainResultError(invalid_use_case);
}
} // namespace core::guard
