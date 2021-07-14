#pragma once

#include <memory>
#include <vector>

#include "./icfg.hpp"

namespace cfg {

class Cfg : public ICfg {
public:
    Cfg(IElement*, ICfg::Blocks, ICfg::Scopes);
    ~Cfg() override;
    auto get_block_by_id(Uuid uuid) const -> IBlock* override;
    auto get_scope_by_id(Uuid uuid) const -> IScope* override;
    class Builder;
    // TODO(dauliac) consider using struct to store object properties
    // and easily pass it from dump/builder/factory.
private:
    const Uuid uuid;
    // TODO(dauliac): not used yet
    IElement* const _element;
    Blocks const _blocks;
    Scopes const _scopes;
};

class Cfg::Builder : public ICfg::IBuilder {
public:
    auto set_uuid(core::Uuid uuid) -> ICfg::IBuilder* override;
    auto add_block(IBlock* block) -> ICfg::IBuilder* override;
    auto add_scope(IScope* scope) -> ICfg::IBuilder* override;
    auto set_blocks(Blocks* blocks) -> ICfg::IBuilder* override;
    auto set_scopes(Scopes* scopes) -> ICfg::IBuilder* override;
    [[nodiscard]] auto build() const -> ICfg* override;

private:
    core::Uuid uuid;
    Blocks* _blocks;
    Scopes* _scopes;
    ICfg* _builded;
};

}  // namespace cfg
