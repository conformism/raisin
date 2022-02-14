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

    [[nodiscard]] auto get_block(Uuid uuid) const
    -> result::Result<Block*, result::Failures::INVALID_UUID, result::Failures::NOT_INSIDE>;
	[[nodiscard]] auto add_block(Block block)
    -> result::Result<Block*, result::Failures::NOT_INSIDE>;
    [[nodiscard]] auto get_statement(Uuid uuid) const
    -> result::Result<Statement*, result::Failures::INVALID_UUID, result::Failures::NOT_INSIDE>;
	[[nodiscard]] auto add_statement(Statement statement)
    -> result::Result<Statement*, result::Failures::NOT_INSIDE>;


private:
    Uuid uuid;
    // TODO(dauliac): not used yet
    // IElement* const _element;
    Blocks _blocks;
    Statements _statements;
};

}  // namespace domain::cfg
