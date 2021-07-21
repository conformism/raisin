#include "types.hpp"

namespace core {
Entity::Entity(Uuid uuid) : _uuid(std::move(uuid)){};

auto Entity::get_uuid() const -> Uuid {
	return _uuid;
}

}  // namespace core
