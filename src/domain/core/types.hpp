#pragma once
#include <any>
#include <map>
#include <memory>
#include <string>
#include <variant>

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
    // TODO(dauliac) Find way to dynamicly compare object types
    // auto operator==(Value rhs) const -> bool;
};

}  // namespace core
