#include "./scope.hpp"

namespace cfg {

Scope::Uuid Scope::get_uuid() const {
	return _uuid;
}

Scope::Blocks Scope::get_blocks() const {
	return _blocks;
}

Scope::Childs Scope::get_childs() const {
	return _childs;
}

Scope::Parent Scope::get_parent() const {
	return _parent;
}

} // namespace cfg
