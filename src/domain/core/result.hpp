#pragma once
#include <memory>
#include <string>
#include <optional>

namespace core::result {

class InvalidUseCaseTypes {
public:
	[[nodiscard]] virtual auto get_name() const -> std::string = 0;
	[[nodiscard]] virtual auto get_reason() const -> std::string = 0;
};

template<typename ValueType, class ErrorType>
class Factory;

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
	virtual auto get_error() const -> ErrorType = 0;
};

template<typename ValueType, class ErrorType>
class BasicDomainResult: public Result<ValueType, ErrorType> {
public:

	[[nodiscard]]
	auto is_success() const -> bool override {
		return _succeed;
	}
	[[nodiscard]]
	auto get_value() const -> ValueType override {
		return _value;
	}
	[[nodiscard]]
	auto get_error() const -> std::optional<ErrorType> override {
		return _error_type;
	}
private:
	bool const _succeed;
	std::optional<ErrorType> const _error_type = std::nullopt;
	ValueType const _value;

	explicit BasicDomainResult(
	  std::optional<ErrorType> const error_type
	) :
	  _succeed(false),
	  _error_type(std::move(error_type))
	{
		_check_type();
	};

	explicit BasicDomainResult(
	  std::optional<ValueType> const value
	) :
	  _succeed(true),
	  _value(value)
	{
		_check_type();
	};

	auto _check_type() const -> void {
		static_assert(
			std::is_base_of<InvalidUseCaseTypes, ErrorType>(),
			"`ErrorType` must extends `InvalidUseCaseTypes`."
		);
	}
};

template<typename Tp>
using ValueType = std::optional<Tp>;
template<typename Tp>
using PointerType = std::unique_ptr<Tp>;

template<typename Vt, class ErrorType>
class ValueResult: public Result<ValueType<Vt>, ErrorType> {
public:
	friend auto Factory<Vt, ErrorType>::create_value_result_success(Vt value);
	friend auto Factory<Vt, ErrorType>::create_value_result_error(Vt value);
private:
	ValueType<Vt> const _value = std::nullopt;
};

template<typename Vt, class ErrorType>
class PointerResult: public Result<PointerType<Vt>, ErrorType> {
public:
	friend auto Factory<Vt, ErrorType>::create_pointer_result_success(Vt value);
	friend auto Factory<Vt, ErrorType>::create_pointer_result_error(Vt value);
private:
	PointerType<Vt> const _value = nullptr;
};

template<typename Vt, class ErrorType>
class Factory {
	public:
		[[nodiscard]]
		static auto create(ValueType<Vt> const value) ->
			Result<ValueType<Vt>, ErrorType>
		{
			return ValueResult<Vt, ErrorType>(std::move(value));
		}
		[[nodiscard]]
		static auto create(PointerType<Vt> const value) -> Result<PointerType<Vt>, ErrorType> {
			return PointerResult<Vt, ErrorType>(value);
		}
		[[nodiscard]]
		static auto create_error(ErrorType const error, bool const is_pointer_variant) -> Result<PointerType<Vt>, ErrorType> {
			if(is_pointer_variant) {
				return ValueResult<Vt, ErrorType>(error);
			}
			return PointerResult<Vt, ErrorType>(error);
		}
	};
}  // namespace core::result
