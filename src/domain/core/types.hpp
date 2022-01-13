#pragma once

#include <any>
#include <map>
#include <memory>
#include <string>

#include "failure-registrar.hpp"
#include "result.hpp"

namespace domain::core {

namespace result {

template<
typename SuccessType,
auto const FirstId,
decltype(FirstId) const... Ids>
class Result;

}  // namespace result

using Uuid = std::string;

constexpr int UUID_LENGTH = 16;
[[nodiscard]] auto create_uuid() -> Uuid;

class Entity {
public:
	[[nodiscard]] auto get_uuid() const -> Uuid;
	[[nodiscard]] auto set_uuid(Uuid uuid) -> result::Result<Uuid, Failures::INVALID_UUID>;

	Entity() = default;
	explicit Entity(Uuid uuid);

private:
	Uuid _uuid = create_uuid();
};

template<class T>
class Value {
public:
	virtual auto operator==(T const& right) const -> bool = 0;
	auto operator!=(T const& right) const -> bool {
		return !(this == right);
	};
};


}  // namespace domain::core
