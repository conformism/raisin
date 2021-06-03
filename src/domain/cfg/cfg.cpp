#include "./cfg.hpp"

namespace cfg {

// Cfg
Cfg::Cfg(IElement* element, ICfg::Blocks blocks, ICfg::Scopes scopes)
: _element(element)
, _blocks(std::move(blocks))
, _scopes(std::move(scopes))
{}

Cfg::~Cfg() = default;

auto Cfg::get_block_by_id(Uuid uuid) const -> IBlock* {
	core::guard::GuardResult const isValidUuidResult = core::guard::is_one_of(uuid, _blocks);

	if(isValidUuidResult.isLeft) {
		return this->_blocks.at(uuid).get();
	}
}

auto Cfg::get_scope_by_id(Uuid uuid) const -> IScope* {
	return this->_scopes.at(uuid).get();
}

} // namespace cfg
