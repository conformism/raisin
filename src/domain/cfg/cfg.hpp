#pragma once

#include <memory>
#include <vector>

#include "domain/core/types.hpp"
#include "domain/core/compositor.hpp"
#include "block.hpp"
#include "compound_statement.hpp"

namespace domain::cfg {

class Cfg : public core::Entity {
public:
	using CompoundStatements = Compositor<CompoundStatement>;
	using Blocks = Compositor<Block>;

    [[nodiscard]] auto get_block(Uuid uuid) const
    -> result::Result<Block*, Failures::INVALID_UUID, Failures::NOT_INSIDE>;
	[[nodiscard]] auto add_block(Block block)
    -> result::Result<Block*, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto add_block(std::unique_ptr<Block> block)
    -> result::Result<Block*, Failures::ALREADY_INSIDE>;
    [[nodiscard]] auto get_compound_statement(Uuid uuid) const
    -> result::Result<CompoundStatement*, Failures::INVALID_UUID, Failures::NOT_INSIDE>;
	[[nodiscard]] auto add_compound_statement(CompoundStatement compound_statement)
    -> result::Result<CompoundStatement*, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto add_compound_statement(std::unique_ptr<CompoundStatement> compound_statement)
    -> result::Result<CompoundStatement*, Failures::ALREADY_INSIDE>;


private:
    Uuid uuid;
    // TODO(dauliac): not used yet
    // IElement* const _element;
    Blocks _blocks;
    CompoundStatements _compound_statements;
};

}  // namespace domain::cfg
