#pragma once
#include <any>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <variant>

namespace core {
using Uuid = std::string;
constexpr int UUID_LENGTH = 16;
[[nodiscard]] auto create_uuid() -> Uuid;

template<class T>
using Compositor = std::map<Uuid, std::unique_ptr<T>>;

class Entity {
public:
	// Security to prevent entity copy in memory
	// Entity(Entity&&) = default;
	// Entity(Entity const&) = delete;
	// auto operator=(Entity const&) -> Entity& = delete;
	// auto operator=(Entity const*) -> Entity& = delete;
	// auto operator=(Entity&&) -> Entity& = delete;

	[[nodiscard]] virtual auto get_uuid() const -> Uuid;

	// protected:
	Entity() = default;
	explicit Entity(Uuid uuid);

private:
	// TODO(dauliac) Add lib to generate random default uuid
	Uuid const _uuid = create_uuid();
};

class Value {
	// TODO(dauliac) Find way to dynamicly compare object types
	// auto operator==(Value rhs) const -> bool;
};

template<class T>
class Builder {
public:
	[[nodiscard]] virtual auto build() -> T = 0;
};

}  // namespace core
