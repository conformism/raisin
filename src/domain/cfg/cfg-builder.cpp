#include "./cfg.hpp"

namespace cfg {

ICfg::IBuilder* Cfg::Builder::set_uuid(core::Uuid uuid) {
	this->uuid = uuid;
	return this;
}

ICfg::IBuilder* Cfg::Builder::add_block(IBlock block) {
	this->_blocks.insert(
		std::pair<Uuid, std::unique_ptr<IBlock>>(block.get_uuid(), &block)
	);
	return this;
}

ICfg::IBuilder* Cfg::Builder::add_scope(IScope scope) {
	this->_scopes.insert(
		std::pair<Uuid, std::unique_ptr<IScope>>(scope.get_uuid(), &scope)
	);
	return this;
}

ICfg::IBuilder* Cfg::Builder::set_blocks(Blocks blocks) {
	this->_blocks = std::move(blocks);
	return this;
}

ICfg::IBuilder* Cfg::Builder::set_scopes(Scopes scopes) {
	this->_scopes = std::move(scopes);
	return this;
}

} // namespace cfg
