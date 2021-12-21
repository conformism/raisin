#pragma once

#include <any>
#include <map>
#include <memory>
#include <string>

#include "failure-registrar.hpp"
#include "result.hpp"

namespace domain::core {

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

}  // namespace domain::core
