#pragma once

#include "./failure-registrar.hpp"

#include "types.hpp"
#include <any>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

namespace core::result {

template<typename E>
class Failure {
public:
	using ErrorCodeRegistrar = E;
	static_assert(
		std::is_enum<ErrorCodeRegistrar>::value,
		"`ErrorCodeRegistrar` must be an enum list of errors.");
	[[nodiscard]] virtual auto get_id() const -> ErrorCodeRegistrar = 0;
	[[nodiscard]] virtual auto get_reason() const -> std::string = 0;
};

template<BasicFailureRegistrar Id>
class BasicFailure : public Failure<BasicFailureRegistrar> {
public:
	explicit BasicFailure(std::string reason) : _reason(std::move(reason)){};
	[[nodiscard]] auto get_id() const -> ErrorCodeRegistrar override {
		return _id;
	};

	[[nodiscard]] auto get_reason() const -> std::string override {
		return _reason;
	};

private:
	ErrorCodeRegistrar _id = Id;
	std::string _reason;
};

// Container to store value of object to transport
template<class T>
struct Success {
	T value;
};

// template<class T>
// constexpr Success<T> success(T const& x) {
//   return {x};
// }

// template<class T>
// Success<T> success(T&& x) {
//   return { std::forward<T>(x) };
// }

// template<class T>
// struct Failure {
//   T value;
// };

// template<class T>
// constexpr Failure<T> failure(T const& x) {
//   return {x};
// }

// template<class T>
// Failure<T> failure(T&& x) {
//   return { std::forward<T>(x) };
// }

/** @brief The Result class is the class that describe the result
 * of a domain action. This result can have a succeed or a failure
 * behavior.
 *
 * @tparam ValueType
 * @todo Add static factory methods/properties to inject logger.
 */
template<class S, class F>
class IEither {
public:
	// static_assert(
	//     std::is_base_of<Success<std::any>, L>(),
	//     "`L` must extends `Success<std::any>`.");
	// static_assert(
	//     std::is_base_of<Failure<std::any>, F>(),
	//     "`F` must extends `Failure<std::any>`.");

	[[nodiscard]] virtual auto is_success() const -> bool = 0;
	[[nodiscard]] virtual auto is_failure() const -> bool = 0;
	[[nodiscard]] virtual auto get_success() const -> std::optional<S> = 0;
	[[nodiscard]] virtual auto get_failure() const -> std::optional<F> = 0;
};

template<typename S, class F>
class Either : public IEither<S, F> {
public:
	[[nodiscard]] constexpr auto is_success() const -> bool override {
		return _is_success;
	}
	[[nodiscard]] constexpr auto is_failure() const -> bool override {
		return !_is_success;
	}
	[[nodiscard]] auto get_success() const -> std::optional<S> override {
		if (_is_success) {
			return std::get<S>(_value);
		}
		return std::nullopt;
	}
	[[nodiscard]] auto get_failure() const -> std::optional<F> override {
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
template<typename S, class F>
using Result = Either<S, F>;

}  // namespace core::result
