#pragma once

#include "result.hpp"
#include "types.hpp"

#include <string>
#include <variant>

namespace core::guard {
class InvalidArgumentParameter: public result::InvalidUseCaseTypes {
public:
	explicit InvalidArgumentParameter(std::string& reason) :
		_name{
			"Invalid-Argument-Parameter",
			std::allocator<char>()
		},
		_reason(reason)
	{}
	[[nodiscard]] auto get_name() const -> std::string override {
		return this->_name;
	}
	[[nodiscard]] auto get_reason() const -> std::string override {
		return this->_reason;
	}
private:
	std::string const _name;
	std::string const _reason;
};

auto against_zero_lenght(
	std::string const* string_to_check,
	std::string const& string_name
) -> std::unique_ptr<result::Result<bool>>;

template<class T>
auto is_one_of(
	Uuid const uuid,
	std::map<Uuid,T*>* collection,
	std::string& collection_name
) -> std::unique_ptr<result::Result<bool>> {
	if(collection->count(uuid) > 0) {
		return result::ResultFactory<bool>
		  ::createBasicDomainResultSuccess(true);
	}

	std::string reason = {"The uuid: ", std::allocator<char>()};
	reason.append(uuid);
	reason.append(" is not present into collection: ");
	reason.append(collection_name);

	const std::optional<core::result::InvalidUseCaseTypes*>
	invalid_use_case = new InvalidArgumentParameter(
		reason
	);
	return result::ResultFactory<T>
	  ::createBasicDomainResultError(invalid_use_case);
}
} // namespace core::guard
