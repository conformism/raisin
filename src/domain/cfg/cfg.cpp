#include "cfg.hpp"
#include "domain/core/guard.hpp"

using namespace std;
namespace domain::cfg {

auto Cfg::get_block(Uuid uuid) const
-> result::Result<Block*, Failures::INVALID_UUID, Failures::NOT_INSIDE>
{
	return _blocks.at(uuid);
}

auto Cfg::add_block(Block block)
-> result::Result<Block*, Failures::ALREADY_INSIDE>
{
	auto const uuid = block.get_uuid();
	return _blocks
		.insert(move(uuid), move(block))
		.set_failures<Failures::ALREADY_INSIDE>()
		.value();
}

auto Cfg::add_block(unique_ptr<Block> block)
-> result::Result<Block*, Failures::ALREADY_INSIDE>
{
	auto const uuid = block->get_uuid();
	return _blocks
		.insert(move(uuid), move(block))
		.set_failures<Failures::ALREADY_INSIDE>()
		.value();
}

auto Cfg::get_compound_statement(Uuid uuid) const
-> result::Result<CompoundStatement*, Failures::INVALID_UUID, Failures::NOT_INSIDE>
{
	return _compound_statements.at(uuid);
}

auto Cfg::add_compound_statement(CompoundStatement compound_statement)
-> result::Result<CompoundStatement*, Failures::ALREADY_INSIDE>
{
	auto const uuid = compound_statement.get_uuid();
	return _compound_statements.insert(move(uuid), move(compound_statement))
	  .set_failures<Failures::ALREADY_INSIDE>().value();
}

}  // namespace domain::cfg
