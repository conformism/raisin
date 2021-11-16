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

namespace domain::core::result {

template<typename FailureType>
class Failure {
public:
	explicit constexpr Failure(FailureType id) : _id(id){};
	[[nodiscard]] constexpr auto get_id() const -> FailureType {
		return _id;
	};

private:
	FailureType const _id;
};

// Container to store value of object to transport
template<typename T>
class Success {
public:
	explicit constexpr Success(T value) : _value(value){};
	[[nodiscard]] constexpr auto get_value() const -> T {
		return _value;
	}
	T _value;
};

template<
	typename SuccessType,
	auto const FirstId = Failures::UNKNOWN,
	decltype(FirstId) const... Ids>
class Result {
public:
	using FailureType = decltype(FirstId);

	template<FailureType const Id>
	[[nodiscard]] static constexpr auto create() -> Result<SuccessType, FirstId, Ids...> {
		constexpr bool is_possible_values = Id == FirstId || ((Id == Ids) || ...);
		static_assert(
			is_possible_values,
			"The given argument parameter Id is not into Ids list {Id, Ids...}");
		return Result<SuccessType, FirstId, Ids...>(Id);
	};
	[[nodiscard]] static constexpr auto create(SuccessType value)
		-> Result<SuccessType, FirstId, Ids...> {
		return Result<SuccessType, FirstId, Ids...>(value);
	};

	[[nodiscard]] constexpr auto is_success() const -> bool {
		return _is_success;
	}
	[[nodiscard]] constexpr auto is_failure() const -> bool {
		return !_is_success;
	}
	[[nodiscard]] constexpr auto get_success() const -> std::optional<SuccessType> {
		if (_is_success) {
			auto const success_value = std::get<Success<SuccessType>>(_value);
			return success_value.get_value();
		}
		return std::nullopt;
	}
	[[nodiscard]] constexpr auto get_failure() const -> std::optional<FailureType> {
		if (_is_success) {
			return std::nullopt;
		}
		auto const failure_value = std::get<Failure<FailureType>>(_value);
		return failure_value.get_id();
	}

	template<FailureType const NewId, FailureType const... NewIds>
	[[deprecated]] [[nodiscard]] constexpr auto append_failures() const {
		auto const result = Result<SuccessType, NewId, FirstId, Ids...>(get_failure().value());
		if constexpr (sizeof...(NewIds) > 1) {
			return result.template append<SuccessType, NewIds...>();
		}
		return result;
	};

	template<typename SettedSuccess>
	[[nodiscard]] constexpr auto set_success() const
		-> std::optional<Result<SettedSuccess, FirstId, Ids...>> {
		if (is_failure()) {
			return Result<SettedSuccess, FirstId, Ids...>(get_failure().value());
		}
		return std::nullopt;
	};

	template<typename SettedSuccess>
	[[nodiscard]] constexpr auto set_success(SettedSuccess setted_success) const
		-> Result<SettedSuccess, FirstId, Ids...> {
		if (is_failure()) {
			return Result<SettedSuccess, FirstId, Ids...>(get_failure().value());
		}
		return Result<SettedSuccess, FirstId, Ids...>(setted_success);
	};

	template<FailureType const... SettedFailures>
	[[nodiscard]] constexpr auto set_failures() const
		-> std::optional<Result<SuccessType, SettedFailures...>> {
		if (is_success()) {
			return Result<SuccessType, SettedFailures...>(get_success().value());
		}
		bool const areNewFailuresValid = ((get_failure().value() == SettedFailures) || ...);
		// bool const areNewFailuresValid = true;
		if (areNewFailuresValid) {
			return Result<SuccessType, SettedFailures...>(get_failure().value());
		}
		return std::nullopt;
	};

	// Error constuctors must be public in fault of combine method recursivity
	explicit constexpr Result(FailureType const value)
		: _is_success(false), _value(Failure<FailureType>(value)){};
	constexpr explicit Result(SuccessType const value)
		: _is_success(true), _value(std::move(Success<SuccessType>{value})){};

private:
	bool const _is_success;
	std::variant<Success<SuccessType>, Failure<FailureType>> const _value{};
};

template<typename SuccessType, auto FirstId = Failures::UNKNOWN, decltype(FirstId) const... Ids>
[[nodiscard]] constexpr auto success(SuccessType const value)
	-> Result<SuccessType, FirstId, Ids...> {
	return Result<SuccessType, FirstId, Ids...>::create(value);
};

template<
	typename SuccessType,
	auto const Value = Failures::UNKNOWN,
	decltype(Value) const FirstPossibleValue = Value,
	decltype(Value) const... PossibleValues>
[[nodiscard]] constexpr auto failure()
	-> Result<SuccessType, FirstPossibleValue, PossibleValues...> {
	return Result<SuccessType, FirstPossibleValue, PossibleValues...>::template create<Value>();
};

}  // namespace domain::core::result
