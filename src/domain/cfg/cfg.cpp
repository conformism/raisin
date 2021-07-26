#include "./cfg.hpp"
#include "../core/guard.hpp"
#include <cstddef>
#include <memory>

namespace cfg {

// Cfg
Cfg::Cfg(
	Uuid uuid,
	IElement* element,
	const Compositor<Block>& blocks,
	const Compositor<Scope>& scopes)
	: ICfg(std::move(uuid)), _element(element), _blocks(&blocks), _scopes(&scopes) {}

auto Cfg::get_block_by_id(Uuid uuid) const -> result::
	Result<result::Success<Block*>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> {
	return guard::is_one_of<Block>(uuid, _blocks, "blocks");
}
auto Cfg::get_scope_by_id(Uuid uuid) const -> result::
	Result<result::Success<Scope*>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> {
	return guard::is_one_of<Scope>(uuid, _scopes, "scopes");
}

}  // namespace cfg
