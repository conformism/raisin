#include "cfg.hpp"
#include "domain/core/guard.hpp"

namespace domain::cfg {

auto Cfg::get_block(Uuid uuid) const
  -> result::Result<Block*, result::Failures::INVALID_UUID, result::Failures::NOT_INSIDE>
{
	return _blocks.at(uuid);
}

auto Cfg::add_block(Block block)
  -> result::Result<Block*, result::Failures::NOT_INSIDE>
{
	auto const uuid = block.get_uuid();
	return _blocks.insert(std::move(uuid), std::move(block))
	  .set_failures<result::Failures::NOT_INSIDE>().value();
}

auto Cfg::get_statement(Uuid uuid) const
	-> result::Result<Statement*, result::Failures::INVALID_UUID, result::Failures::NOT_INSIDE> {
	return _statements.at(uuid);
}

auto Cfg::add_statement(Statement statement)
  -> result::Result<Statement*, result::Failures::NOT_INSIDE>
{
	auto const uuid = statement.get_uuid();
	return _statements.insert(std::move(uuid), std::move(statement))
	  .set_failures<result::Failures::NOT_INSIDE>().value();
}

}  // namespace domain::cfg
