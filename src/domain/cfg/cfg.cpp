#include "./cfg.hpp"

namespace cfg {

// Cfg
Cfg::Cfg(IElement* element, ICfg::Blocks blocks, ICfg::Scopes scopes)
: _element(element)
, _blocks(std::move(blocks))
, _scopes(std::move(scopes))
{}

Cfg::~Cfg() {}

IBlock* Cfg::get_block_by_id(Uuid uuid) const {
	return this->_blocks.at(uuid).get();
}

IScope* Cfg::get_scope_by_id(Uuid uuid) const {
	return this->_scopes.at(uuid).get();
}

} // namespace cfg
