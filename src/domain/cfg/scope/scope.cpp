#include "./scope.hpp"

namespace cfg {

auto Scope::get_blocks() const -> Scope::Blocks {
	return _blocks;
}

auto Scope::get_childs() const -> Scope::Childs {
	return _childs;
}

auto Scope::get_parent() const -> Scope::Parent {
	return _parent;
}

}  // namespace cfg
