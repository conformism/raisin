#include "./cfg.hpp"

namespace cfg {

ICfg::IBuilder* Cfg::Builder::set_uuid(core::Uuid uuid) {
	this->uuid = uuid;
	return this;
}

ICfg::IBuilder* Cfg::Builder::set_blocks(Blocks blocks) {
	this->_blocks = std::move(blocks);
	return this;
}


} // namespace cfg
