#pragma once
#include <variant>
#include <string>
#include <map>
#include <memory>

namespace core {
using Uuid = std::string;

template<class T>
using Aggregator = std::map<Uuid, std::shared_ptr<T>>;

template<class T>
using Compositor = std::map<Uuid, std::unique_ptr<T>>;

class Entity {
public:
	Entity(Entity const&) = delete;
	auto operator=(Entity const*) -> Entity& = delete;

	[[nodiscard]] virtual auto get_uuid() const -> Uuid;
protected:
	explicit Entity(Uuid uuid);
	~Entity() = default;
private:
	Uuid const _uuid;
};

class Value {
	auto operator==(const Entity* rhs) const -> bool;
};

}  // namespace core
