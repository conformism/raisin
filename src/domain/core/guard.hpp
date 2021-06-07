#pragma once

#include "result.hpp"
#include "types.hpp"

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
		return this->_name;
	}
	[[nodiscard]]
	auto get_reason() const -> std::string override {
		return this->_reason;
	}
private:
	std::string const _name;
	std::string const _reason;
};

auto against_zero_lenght(
	std::string const* string_to_check,
	std::string const* string_name
) -> std::unique_ptr<result::Result<std::string>>;

template<class Contained>
auto is_one_of(
	Uuid const& uuid,
	std::map<Uuid, Contained*>* collection,
	std::string& collection_name
) -> std::unique_ptr<result::Result<Contained>> {
	if(collection->count(uuid) > 0) {
		Contained const* contained = collection->at(uuid);
		return result::ResultFactory<Contained>
		  ::createBasicDomainResultSuccess(contained);
	}

	std::string reason = "No Contained at uuid: " + uuid + " is not present into collection: " + collection_name;
	reason.append(collection_name);

	InvalidArgumentParameter const* invalid_use_case = new InvalidArgumentParameter(
		reason
	);

	return result::ResultFactory<Contained>
	  ::createBasicDomainResultError(invalid_use_case);
}
} // namespace core::guard
