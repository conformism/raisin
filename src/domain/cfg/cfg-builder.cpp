#include "./cfg.hpp"
#include <memory>

namespace cfg {

auto Cfg::Builder::set_uuid(core::Uuid uuid) -> ICfg::IBuilder* {
	uuid = uuid;
	return this;
}

auto Cfg::Builder::add_block(Block* block) -> ICfg::IBuilder* {
	_blocks->insert_or_assign(block->get_uuid(), block);
	return this;
}

auto Cfg::Builder::add_scope(Scope* scope) -> ICfg::IBuilder* {
	_scopes->insert_or_assign(scope->get_uuid(), scope);
	return this;
}

auto Cfg::Builder::set_blocks(Aggregator<Block>* blocks) -> ICfg::IBuilder* {
	_blocks = blocks;
	return this;
}

auto Cfg::Builder::set_scopes(Aggregator<Scope>* scopes) -> ICfg::IBuilder* {
	_scopes = scopes;
	return this;
}

auto Cfg::Builder::build() const -> Cfg {
	Cfg _builded = Cfg(_uuid, *_blocks, *_scopes);
	return _builded;
}
}  // namespace cfg
