#include "./cfg.hpp"
#include "../core/guard.hpp"
#include <cstddef>
#include <memory>

namespace cfg {

// Cfg
Cfg::Cfg(
	Uuid uuid,
	IElement* element,
	const Aggregator<Block>& blocks,
	const Aggregator<Scope>& scopes)
	: ICfg(std::move(uuid)), _element(element), _blocks(&blocks), _scopes(&scopes) {}

auto Cfg::get_block_by_id(Uuid uuid) const
	-> result::BasicDomainResult<std::weak_ptr<Block>, guard::InvalidArgumentParameter> {
	return guard::is_one_of<Block>(uuid, _blocks, "blocks");
}
auto Cfg::get_scope_by_id(Uuid uuid) const
	-> result::BasicDomainResult<std::weak_ptr<Scope>, guard::InvalidArgumentParameter> {
	return guard::is_one_of<Scope>(uuid, _scopes, "scopes");
}

}  // namespace cfg
