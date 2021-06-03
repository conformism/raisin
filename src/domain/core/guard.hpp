#pragma once

#include "result.hpp"
#include "types.hpp"

#include <string>
#include <variant>

namespace core::guard {
	class InvalidArgumentParameter: public result::InvalidUseCaseTypes {
	public:
		InvalidArgumentParameter(std::string name, std::string reason);
		[[nodiscard]] auto get_name() const -> std::string override;
		[[nodiscard]] auto get_reason() const -> std::string override;
	private:
		std::string const _name;
		std::string const _reason;
	};

	template<class T>
	using IdexedCollection = std::variant<Compositor<T>, Aggregator<T>>;

	template<class T>
	auto is_one_of(
		Uuid const uuid,
		std::map<Uuid,T*>* collection,
		std::string& collection_name
	) -> result::Result<bool> {
		if(collection->count(uuid) > 0) {
			return result::ResultFactory<T>
			  ::createBasicDomainResultSuccess(true);
		}

		std::string name = {
			"Invalid-Argument-Parameter",
			std::allocator<char>()
		};
		std::string reason = {"The uuid: ", std::allocator<char>()};
		reason.append(uuid);
		reason.append(" is not present into collection: ");
		reason.append(collection_name);

		const std::optional<core::result::InvalidUseCaseTypes*>
		  invalid_use_case = new InvalidArgumentParameter(
			name,
			reason
		  );
		return result::ResultFactory<T>
		  ::createBasicDomainResultError(invalid_use_case);
	}
} // namespace core::guard
