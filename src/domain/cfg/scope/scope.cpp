#include "./scope.hpp"
#include <algorithm>
#include <utility>

namespace cfg {

Scope::Scope(Parent parent, Childs childs, Blocks blocks)
	: IScope<Scope, Block>(),
	  _parent(parent),
	  _blocks(std::move(blocks)),
	  _childs(std::move(childs)){};

Scope::Scope(core::Uuid uuid, Parent parent, Childs childs, Blocks blocks)
	: IScope(std::move(uuid)),
	  _parent(parent),
	  _blocks(std::move(blocks)),
	  _childs(std::move(childs)){};

auto Scope::is_root() const -> bool {
	auto const is_root = _parent == nullptr;
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
