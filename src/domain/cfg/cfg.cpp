#include "./cfg.hpp"
#include "../core/guard.hpp"
#include <cstddef>
#include <memory>
#include <utility>

namespace cfg {

// Cfg
Cfg::Cfg(
	// IElement* element,
	Aggregator<Block> blocks,
	Aggregator<Scope> scopes)
	:  // _element(element),
	  _blocks(std::move(blocks)),
	  _scopes(std::move(scopes)) {}

Cfg::Cfg(
	Uuid uuid,
	// IElement* element,
	Aggregator<Block> blocks,
	Aggregator<Scope> scopes)
	: ICfg(std::move(uuid)),
	  // _element(element),
	  _blocks(std::move(blocks)),
	  _scopes(std::move(scopes)) {}

auto Cfg::get_block_by_id(Uuid uuid) const -> result::
	Result<result::Success<Block*>, result::BasicFailure<Failures::NOT_INSIDE>> {
	return _blocks.at(uuid);
}
auto Cfg::get_scope_by_id(Uuid uuid) const -> result::
	Result<result::Success<Scope*>, result::BasicFailure<Failures::NOT_INSIDE>> {
	return _scopes.at(uuid);
}

}  // namespace cfg
