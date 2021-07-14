#pragma once
#include "types.hpp"
#include <memory>
#include <optional>
#include <string>
#include <utility>

namespace core::result {

class InvalidUseCaseTypes {
public:
	[[nodiscard]] virtual auto get_name() const -> std::string = 0;
	[[nodiscard]] virtual auto get_reason() const -> std::string = 0;
};
template<typename ValueType, class ErrorType>
class Factory;

class BasicInvalidUseCase: public InvalidUseCaseTypes, public Value {
public:
	BasicInvalidUseCase(std::string name, std::string reason) :
		_name(std::move(name)),
		_reason(std::move(reason))
	{};
	[[nodiscard]]  auto get_name() const -> std::string override {
		return _name;
	};
	[[nodiscard]] auto get_reason() const -> std::string override {
		return _reason;
	};
	auto operator==(const InvalidUseCaseTypes& rhs) const -> bool {
		const auto areEquals = rhs.get_name() == get_name() && rhs.get_reason() == get_reason();
		return areEquals;
	};
private:
	std::string const _name;
	std::string const _reason;
};


/**
 * @brief The Result class is the class that describe the result
 * of a domain action. This result can have a succeed or a failure
 * behavior.
 *
 * @tparam ValueType
 * @todo Add static factory methods/properties to inject logger.
 */
template<typename ValueType, class ErrorType>
class Result {
public:
	[[nodiscard]]
	virtual auto is_success() const -> bool = 0;
	[[nodiscard]]
	virtual auto get_value() const -> std::optional<ValueType> = 0;
	[[nodiscard]]
	virtual auto get_error() const -> std::optional<ErrorType> = 0;
};

template<typename ValueType, class ErrorType>
class BasicDomainResult: public Result<ValueType, ErrorType> {
public:

	[[nodiscard]]
	auto is_success() const -> bool override {
		return _succeed;
	}
	[[nodiscard]]
	auto get_value() const -> std::optional<ValueType> override {
		return _value;
	}
	[[nodiscard]]
	auto get_error() const -> std::optional<ErrorType> override {
		return _error_type;
	}
private:
	// TODO(dauliac) check If we can friend only create methods about BasicDomainResult
	friend Factory<ValueType, ErrorType>;

	explicit BasicDomainResult(
	  ErrorType error_type
	) :
	  _succeed(false),
	  _error_type(std::move(error_type))
	{
		_check_type();
	};

	explicit BasicDomainResult(
	  ValueType value
	) :
	  _value(value)
	  ,_succeed(true)
	{
		_check_type();
	};

	auto _check_type() const -> void {
		static_assert(
			std::is_base_of<InvalidUseCaseTypes, ErrorType>(),
			"`ErrorType` must extends `InvalidUseCaseTypes`."
		);
	}

	bool const _succeed;
	std::optional<ErrorType> const _error_type = std::nullopt;
	std::optional<ValueType> const _value = std::nullopt;
};

// template<typename Tp>
// using PointerType = std::unique_ptr<Tp>;

// template<typename Vt, class ErrorType>
// class ValueResult: public BasicDomainResult<Vt, ErrorType> {
// public:
//     explicit ValueResult(Vt value) :
//         BasicDomainResult<Vt, ErrorType>(value)
//     {}
//     explicit ValueResult(ErrorType error) :
//         BasicDomainResult<Vt, ErrorType>(error)
//     {}
//     // friend auto Factory<Vt, ErrorType>::create(Vt value);
//     // friend auto Factory<Vt, ErrorType>::create_error(Vt value);
// private:
//     std::optional<Vt> _value = std::nullopt;
// };

// TODO(dauliac) Useless, you can pass unique_ptr to value template
// template<typename Vt, class ErrorType>
// class PointerResult: public BasicDomainResult<PointerType<Vt>, ErrorType> {
// public:
//     explicit PointerResult(PointerType<Vt> pointer) :
//         BasicDomainResult<PointerType<Vt>, ErrorType>(pointer)
//     {}
//     explicit PointerResult(ErrorType error) :
//         BasicDomainResult<PointerType<Vt>, ErrorType>(error)
//     {}
//     // friend auto Factory<Vt, ErrorType>::create(Vt value);
//     // friend auto Factory<Vt, ErrorType>::create_error(Vt value);
// private:
//     PointerType<Vt> _value = nullptr;
// };

template<typename Vt, class ErrorType>
class Factory {
	public:
		[[nodiscard]]
		static auto create(Vt value) -> BasicDomainResult<Vt, ErrorType>
		{
			return BasicDomainResult<Vt, ErrorType>(std::move(value));
		}
		// [[nodiscard]]
		// static auto create(PointerType<Vt> const pointer) -> PointerResult<Vt, ErrorType> {
		//     return PointerResult<Vt, ErrorType>(std::move(pointer));
		// }
		[[nodiscard]]
		static auto create(ErrorType const error) -> BasicDomainResult<Vt, ErrorType> {
			return BasicDomainResult<Vt, ErrorType>(std::move(error));
		}
	};
}  // namespace core::result
