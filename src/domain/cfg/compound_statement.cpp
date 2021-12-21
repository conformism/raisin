#include <algorithm>
#include <utility>

#include "compound_statement.hpp"
#include "domain/core/guard.hpp"

namespace domain::cfg {

auto CompoundStatement::is_root() const -> bool {
	auto const is_root = _parent == nullptr;
	return is_root;
}

auto CompoundStatement::has_childs() const -> bool {
	auto const has_childs = !_childs.empty();
	return has_childs;
}

auto CompoundStatement::get_childs() const -> CompoundStatement::Childs const* {
	return &_childs;
}

auto CompoundStatement::add_child(CompoundStatement const* child)
-> result::Result<CompoundStatement const*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>
{
	return _childs.insert(child->get_uuid(), child)
	  .set_failures<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>().value();
}

auto CompoundStatement::get_blocks() const -> CompoundStatement::Blocks const* {
	return &_blocks;
}

auto CompoundStatement::add_block(Block const* block)
-> result::Result<Block const*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>
{
	return _blocks.insert(block->get_uuid(), block)
	  .set_failures<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>().value();
}

auto CompoundStatement::get_parent() const -> CompoundStatement::Parent const* {
	return &_parent;
}

auto CompoundStatement::set_parent(CompoundStatement const* parent)
-> result::Result<CompoundStatement const*, Failures::NO_RESOURCES, Failures::ALREADY_SETTED>
{
	auto guard_result = guard::is_null_pointer<CompoundStatement const>(parent);
	if(guard_result.is_failure()) {
		return guard_result.set_failures<Failures::NO_RESOURCES, Failures::ALREADY_SETTED>().value();

	}
	if(_parent->get_uuid() == parent->get_uuid()) {
		return result::failure<CompoundStatement const*, Failures::ALREADY_SETTED, Failures::NO_RESOURCES, Failures::ALREADY_SETTED>();
	}
	_parent = parent;
	return result::success<CompoundStatement const*, Failures::NO_RESOURCES, Failures::ALREADY_SETTED>(parent);
}


}  // namespace domain::cfg
