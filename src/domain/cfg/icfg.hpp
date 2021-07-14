#pragma once

#include "../core/types.hpp"

#include "./block/iblock.hpp"
#include "./element/ielement.hpp"
#include "./scope/iscope.hpp"

namespace cfg {

class ICfg {
public:
    using Uuid = core::Uuid;
    using Blocks = core::Compositor<IBlock>;
    using Scopes = core::Compositor<IScope>;

    virtual ~ICfg() = default;
    [[nodiscard]] virtual auto get_uuid(Uuid uuid) const -> Uuid = 0;
    [[nodiscard]] virtual auto get_block_by_id(Uuid uuid) const -> IBlock* = 0;
    [[nodiscard]] virtual auto get_scope_by_id(Uuid uuid) const -> IScope* = 0;

    class IBuilder {
    public:
        virtual ~IBuilder() = default;
        virtual auto set_uuid(core::Uuid uuid) -> IBuilder* = 0;
        virtual auto add_block(IBlock* block) -> IBuilder* = 0;
        virtual auto add_scope(IScope* scope) -> IBuilder* = 0;
        virtual auto set_blocks(Blocks* blocks) -> IBuilder* = 0;
        virtual auto set_scopes(Scopes* scopes) -> IBuilder* = 0;
        [[nodiscard]] virtual auto build() const -> ICfg* = 0;
    };
};

}  // namespace cfg
