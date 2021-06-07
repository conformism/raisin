#pragma once
#include <memory>
#include <string>
#include <utility>
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

	template<class ValueType>
	class BasicDomainResult;

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
		virtual auto get_value() const -> const ValueType* = 0;
		[[nodiscard]]
		virtual auto get_error() const -> const InvalidUseCaseTypes* = 0;

		class Factory {
		public:
			[[nodiscard]]
			static auto createBasicDomainResultSuccess(ValueType const* value) -> std::unique_ptr<Result<ValueType>> {
				BasicDomainResult<ValueType> const result = *new BasicDomainResult<ValueType>(value);
				return std::make_unique<BasicDomainResult<ValueType>>(
					result
				);
			}
			[[nodiscard]]
			static auto createBasicDomainResultError(InvalidUseCaseTypes const* error) -> std::unique_ptr<Result<ValueType>> {
				BasicDomainResult<ValueType> const result_error = *new BasicDomainResult<ValueType>(error);
				return std::make_unique<BasicDomainResult<ValueType>>(
					result_error
				);
			}
		};
	};

	template<class ValueType>
	class BasicDomainResult: public Result<ValueType> {
	public:

		friend auto Result<ValueType>::Factory::createBasicDomainResultSuccess(const ValueType *value);
		friend auto Result<ValueType>::Factory::createBasicDomainResultError(const InvalidUseCaseTypes *error);

		[[nodiscard]]
		auto is_success() const -> bool override {
			return _succeed;
		}
		[[nodiscard]]
		auto get_value() const -> const ValueType* override {
			if(!is_success()) {
				throw std::logic_error("Can't get value on error Result. Please use is_success() methods before.");
			}
			return _value;
		}
		[[nodiscard]]
		auto get_error() const -> const InvalidUseCaseTypes* override {
		// auto get_error() const -> InvalidUseCaseTypes* {
			if(!is_success()) {
				throw std::logic_error("Can't get error on value Result. Please use is_success() methods before.");
			}
			return _error_type;
		}
	private:
		bool const _succeed;
		InvalidUseCaseTypes const* _error_type = nullptr;
		ValueType const* _value = nullptr;

		explicit BasicDomainResult(
		  InvalidUseCaseTypes const* error_type
		) :
		  _succeed(false),
		  _error_type(error_type)
		{};
		explicit BasicDomainResult(
		  ValueType const* value
		) :
		  _succeed(true),
		  _value(value) {};
	};

}  // namespace core::result
