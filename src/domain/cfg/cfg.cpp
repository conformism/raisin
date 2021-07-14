#include "./cfg.hpp"

namespace cfg {

// Cfg
Cfg::Cfg(Uuid uuid, IElement* element, ICfg::Blocks blocks, ICfg::Scopes scopes)
    : ICfg(std::move(uuid)),
      _element(element),
      _blocks(std::move(blocks)),
      _scopes(std::move(scopes)) {}

auto Cfg::get_block_by_id(Uuid uuid) const -> IBlock* {
    // core::guard::GuardResult const isValidUuidResult = core::guard::is_one_of(uuid, _blocks);
    // if(isValidUuidResult.isLeft) {
    //     return _blocks.at(uuid).get();
    // }

    return _blocks.at(uuid).get();
}

auto Cfg::get_scope_by_id(Uuid uuid) const -> IScope* {
    return _scopes.at(uuid).get();
}

}  // namespace cfg
