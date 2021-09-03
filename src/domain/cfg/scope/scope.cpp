#include "./scope.hpp"

namespace cfg {

auto Scope::is_root() const -> bool {
	auto const is_root = !_parent.has_value();
	return is_root;
}

auto Scope::has_childs() const -> bool {
	auto const has_childs = !_childs.empty();
	return has_childs;
}

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
