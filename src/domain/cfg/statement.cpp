#include "./statement.hpp"
#include <algorithm>
#include <utility>

namespace domain::cfg {

auto Statement::is_root() const -> bool {
	auto const is_root = _parent == nullptr;
	return is_root;
}

auto Statement::has_childs() const -> bool {
	auto const has_childs = !_childs.empty();
	return has_childs;
}

auto Statement::get_blocks() const -> Statement::Blocks {
	return _blocks;
}

auto Statement::get_childs() const -> Statement::Childs {
	return _childs;
}

auto Statement::get_parent() const -> Statement::Parent {
	return _parent;
}

}  // namespace domain::cfg
