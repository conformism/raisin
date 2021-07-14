#include "./cfg.hpp"

namespace cfg {

auto Cfg::Builder::set_uuid(core::Uuid uuid) -> ICfg::IBuilder* {
    uuid = uuid;
    return this;
}

auto Cfg::Builder::add_block(IBlock* block) -> ICfg::IBuilder* {
    _blocks->insert(std::pair<Uuid, std::unique_ptr<IBlock>>(block->get_uuid(), block));
    return this;
}

auto Cfg::Builder::add_scope(IScope* scope) -> ICfg::IBuilder* {
    _scopes->insert(std::pair<Uuid, std::unique_ptr<IScope>>(scope->get_uuid(), scope));
    return this;
}

auto Cfg::Builder::set_blocks(Blocks* blocks) -> ICfg::IBuilder* {
    _blocks = blocks;
    return this;
}

auto Cfg::Builder::set_scopes(Scopes* scopes) -> ICfg::IBuilder* {
    _scopes = scopes;
    return this;
}

}  // namespace cfg
