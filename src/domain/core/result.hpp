#pragma once
#include <string>
#include <variant>
#include <optional>
#include <stdexcept>

namespace core::result {

	enum FatalErrors {
		INVALID_ARGUMENT_PARAMETER
	};
	class InvalidUseCaseTypes {
	public:
		[[nodiscard]] virtual auto get_name() const -> std::string = 0;
		[[nodiscard]] virtual auto get_reason() const -> std::string = 0;
	};

	/**
	 * @brief The Result class is the class that describe the result
	 * of a domain action. This result can have a succeed or a failure
	 * behavior.
	 *
	 * @tparam ValueType
	 * @todo Add static factory methods/properties to inject logger.
	 */
	template<class ValueType>
	class Result {
	public:
		[[nodiscard]]
		virtual auto is_success() const -> bool = 0;
		[[nodiscard]]
		virtual auto get_value() const -> std::optional<ValueType*> = 0;
		[[nodiscard]]
		virtual auto get_error() const -> std::optional<InvalidUseCaseTypes*> = 0;
	};

	template<class ValueType>
	class BasicDomainResult: public Result<ValueType> {
	public:
		explicit BasicDomainResult(
		  bool succeed,
		  std::optional<InvalidUseCaseTypes*> error_type,
		  std::optional<ValueType*> value
		) :
		  _succeed(succeed),
		  _error_type(error_type),
		  _value(value)
		{};
		explicit BasicDomainResult(
		  std::optional<InvalidUseCaseTypes*> error_type
		) :
		  _succeed(false),
		  _error_type(error_type)
		{};
		explicit BasicDomainResult(
		  std::optional<ValueType*> value
		) :
		  _succeed(true),
		  _value(value) {};

		[[nodiscard]]
		auto is_success() const -> bool {
			return this->_succeed;
		}
		[[nodiscard]]
		auto get_value() const -> std::optional<ValueType*> {
			return this->_value;
		}
		[[nodiscard]]
		auto get_error() const -> std::optional<InvalidUseCaseTypes*> {
			return this->_error_type;
		}
	private:
		bool const _succeed;
		std::optional<InvalidUseCaseTypes*> const _error_type = std::nullopt;
		std::optional<ValueType*> const _value = std::nullopt;
	};

	template<class ValueType>
	class ResultFactory {
	public:
		static auto createBasicDomainResultSuccess(ValueType* value) -> Result<ValueType*>  {
			if(value != nullptr) {
				return new result::BasicDomainResult<ValueType>(value);
			}
    		throw std::invalid_argument("Your result::Result object can't have nullptr value.");
		}
		static auto createBasicDomainResultError(InvalidUseCaseTypes* error) -> Result<ValueType*> {
			if(error != nullptr) {
				return new result::BasicDomainResult<ValueType>(error);
			}
    		throw std::invalid_argument("Your result::Result can't have nullptr error.");
		}
	};
	// template<class ValueType>
	// auto error(InvalidUseCaseTypes error_type) const -> Result<class ValueType> {
	// }

}  // namespace core::result
