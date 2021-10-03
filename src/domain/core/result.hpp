#pragma once

#include "failure-registrar.hpp"
#include "types.hpp"

#include <algorithm>
#include <any>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
// #include <type_traits>

namespace core::result {

template<Failures idValue>
class Failure {
public:
	using IdType = decltype(idValue);

	[[nodiscard]] auto get_id() const -> IdType {
		return _id;
	};

private:
	IdType const _id = idValue;
	std::string _reason;
};

// Container to store value of object to transport
template<typename T = std::any>
class Success {
public:
	[[nodiscard]] auto get_value() const -> T {
		return value;
	}
	T value;
};

/** @brief The IEither class is the class that describe the result
 * of a domain action. This result can have a succeed or a failure
 * behavior.
 *
 * @tparam S Sucess template
 * @tparam S F Failure template
 * @todo Add static factory methods/properties to inject logger.
 * @todo Find way to static assert with typing constraint:
 *   - Using create methods ?
 *   - Using Factory ?
 */

template<class SuccessType, auto FirstId = Failures::UNKNOWN, decltype(FirstId) const... Ids>
class Result {
public:
	using FailureType = decltype(FirstId);

	template<FailureType Id>
	static constexpr auto create() -> Result<SuccessType, FirstId, Ids...> {
		constexpr bool is_possible_values = Id == FirstId || ((Id == Ids) || ...);
		static_assert(
			is_possible_values,
			"The given arguemnt parameter Id is not into Ids list {Id, Ids...}");
		return Result(Id);
	};

	template<SuccessType value>
	static constexpr auto createi() -> Result<SuccessType, FirstId, Ids...> {
		return Result(value);
	};
	[[nodiscard]] constexpr auto is_success() const -> bool {
		return _is_success;
	}
	[[nodiscard]] constexpr auto is_failure() const -> bool {
		return !_is_success;
	}
	[[nodiscard]] constexpr auto get_succes() const -> SuccessType {
		return std::get<SuccessType>(_value);
	}
	[[nodiscard]] constexpr auto get_failure() const -> FailureType {
		FailureType const id = std::get<Failure<_value>>(_value).get_id;
		return id;
	}
	constexpr explicit Result(SuccessType const value)
		: _is_success(true), _value(std::move(Success<SuccessType>{value})){};
	constexpr explicit Result(FailureType const value)
		: _is_success(false), _value(Failure<value>()){};

private:
	bool const _is_success;
	std::variant<Success<SuccessType>, Failure<FirstId>> const _value{};
};

}  // namespace core::result
