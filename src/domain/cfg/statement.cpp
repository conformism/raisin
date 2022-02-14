#include <algorithm>
#include <utility>

#include "statement.hpp"
#include "domain/core/guard.hpp"

namespace domain::cfg {

auto Statement::is_root() const -> bool {
	auto const is_root = _parent == nullptr;
	return is_root;
}

auto Statement::has_childs() const -> bool {
	auto const has_childs = !_childs.empty();
	return has_childs;
}

auto Statement::get_childs() const -> Statement::Childs const* {
	return &_childs;
}

auto Statement::add_child(Statement const* child)
  -> result::Result<Statement const*, result::Failures::NO_RESOURCES, result::Failures::ALREADY_INSIDE>
{
	return _childs.insert(child->get_uuid(), child)
	  .set_failures<result::Failures::NO_RESOURCES, result::Failures::ALREADY_INSIDE>().value();
}

auto Statement::get_blocks() const -> Statement::Blocks const* {
	return &_blocks;
}

auto Statement::add_block(Block const* block)
  -> result::Result<Block const*, result::Failures::NO_RESOURCES, result::Failures::ALREADY_INSIDE>
{
	return _blocks.insert(block->get_uuid(), block)
	  .set_failures<result::Failures::NO_RESOURCES, result::Failures::ALREADY_INSIDE>().value();
}

auto Statement::get_parent() const -> Statement::Parent const* {
	return &_parent;
}

auto Statement::set_parent(Statement const* parent)
  -> result::Result<Statement const*, result::Failures::NO_RESOURCES, result::Failures::ALREADY_SETTED>
{
	auto guard_result = guard::is_null_pointer<Statement const>(parent);
	if(guard_result.is_failure()) {
		return guard_result.set_failures<result::Failures::NO_RESOURCES, result::Failures::ALREADY_SETTED>().value();

	}
	if(_parent->get_uuid() == parent->get_uuid()) {
		return result::failure<Statement const*, result::Failures::ALREADY_SETTED, result::Failures::NO_RESOURCES, result::Failures::ALREADY_SETTED>();
	}
	_parent = parent;
	return result::success<Statement const*, result::Failures::NO_RESOURCES, result::Failures::ALREADY_SETTED>(parent);
}


}  // namespace domain::cfg
