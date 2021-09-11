#pragma once

#include "failure-registrar.hpp"
#include "types.hpp"

#include <algorithm>
#include <any>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>
// #include <type_traits>

namespace core::result {

template<typename ErrorCodeRegistrar>
class Failure {
public:
	static_assert(
		std::is_enum<ErrorCodeRegistrar>::value,
		"`ErrorCodeRegistrar` must be an enum list of errors.");
	[[nodiscard]] virtual auto get_id() const -> ErrorCodeRegistrar = 0;
};

template<auto IdDefault = BasicFailureRegistrar::NOTHING, decltype(IdDefault) const... Ids>
class BasicFailure : public Failure<decltype(IdDefault)> {
public:
	using IdType = decltype(IdDefault);
	constexpr explicit BasicFailure(IdType const id = IdDefault) : _id(id) {
		std::vector<IdType> const possible_values = std::vector<IdType>{IdDefault, Ids...};
		bool const not_in_possible_values =
			1 > std::count(possible_values.begin(), possible_values.end(), id);
		// TODO(dauliac) Use something at compile time instead of runtime
		// static_assert(
		//     count < 1, "The given arguemnt parameter Id is not into Ids list {Id, Ids...}");
		if (not_in_possible_values) {
			throw std::invalid_argument(
				"The given arguemnt parameter Id is not into Ids list {Id, Ids...}");
		}
	};
	[[nodiscard]] auto get_id() const -> IdType override {
		return _id;
	};

private:
	IdType const _id;
	std::string _reason;
};

// Container to store value of object to transport
template<typename T = std::any>
class Success {
public:
	[[nodiscard]] auto get_value() const -> T {
		return value;
	}
	T const value;
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
template<typename S, typename F>
class IEither {
public:
	// static_assert(
	//     std::is_base_of<Success<>, S<>(),
	//     "`L` must extends `Success<std::any>`.");
	// static_assert(
	//     std::is_base_of<Failure<FValue>, F<FValue>>(),
	//     "`F` must extends `Failure<std::any>`.");

	[[nodiscard]] virtual auto is_success() const -> bool = 0;
	[[nodiscard]] virtual auto is_failure() const -> bool = 0;
	[[nodiscard]] virtual auto get_success() const -> std::optional<S> = 0;
	[[nodiscard]] virtual auto get_failure() const -> std::optional<F> = 0;
};

template<class S = Success<>, class F = BasicFailure<>>
class Either : public IEither<S, F> {
public:
	[[nodiscard]] constexpr auto is_success() const -> bool override {
		return _is_success;
	}
	[[nodiscard]] constexpr auto is_failure() const -> bool override {
		return !_is_success;
	}
	[[nodiscard]] constexpr auto get_success() const -> std::optional<S> override {
		if (_is_success) {
			return std::get<S>(_value);
		}
		return std::nullopt;
	}
	[[nodiscard]] constexpr auto get_failure() const -> std::optional<F> override {
		if (!_is_success) {
			return std::get<F>(_value);
		}
		return std::nullopt;
	}
	constexpr explicit Either(S const value) : _is_success(true), _value(std::move(value)){};
	constexpr explicit Either(F const value) : _is_success(false), _value(std::move(value)){};

private:
	bool const _is_success;
	std::variant<S, F> const _value;
};

// To allow changing result object without renaming all objects in source Enumcode.
template<typename S = Success<>, class F = BasicFailure<>>
using Result = Either<S, F>;

}  // namespace core::result
