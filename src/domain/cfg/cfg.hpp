#pragma once

#include <memory>
#include <vector>

#include "domain/core/types.hpp"
#include "domain/core/compositor.hpp"
#include "block.hpp"
#include "statement.hpp"

namespace domain::cfg {

class Cfg : public core::Entity {
public:
	using Statements = Compositor<Statement>;
	using Blocks = Compositor<Block>;

    [[nodiscard]] auto get_block_by_id(Uuid uuid) const
    -> result::Result<Block*, Failures::INVALID_UUID, Failures::NOT_INSIDE>;
    [[nodiscard]] auto get_scope_by_id(Uuid uuid) const
    -> result::Result<Statement*, Failures::INVALID_UUID, Failures::NOT_INSIDE>;

private:
    Uuid uuid;
    // TODO(dauliac): not used yet
    // IElement* const _element;
    Blocks _blocks;
    Statements _statements;
};

}  // namespace domain::cfg
