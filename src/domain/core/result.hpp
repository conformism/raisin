#pragma once
#include <variant>
#include <optional>

namespace core {
namespace result {
	enum InvalidUseCaseTypes {
		NOT_FOUND,
	};

	template<class ValueType>
	class Result {
	public:
		explicit Result(
		  bool failed,
		  std::optional<InvalidUseCaseTypes> error_type = std::nullopt,
		  std::optional<ValueType> value = std::nullopt
		);
		auto is_success() const -> bool;
		auto is_failure() const -> bool;
		auto get_value() const -> ValueType*;
	private:
		bool const _failed;
		InvalidUseCaseTypes const _error_type;
		ValueType* const std::optionnal<ValueType>;
	}
} // namespace result
} // namespace core
