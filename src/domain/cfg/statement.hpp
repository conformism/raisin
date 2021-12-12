#pragma once

#include "domain/core/types.hpp"
#include "block.hpp"

namespace domain::cfg {

using namespace domain::core;

class Statement: public core::Entity {
public:
	using Parent = Statement const*;
	using Blocks = Aggregator<Block const>;
	using Childs = Aggregator<Statement const>;

	[[nodiscard]] auto is_root() const -> bool;
	[[nodiscard]] auto has_childs() const -> bool;
	[[nodiscard]] auto get_childs() const -> Childs const*;
	[[nodiscard]] auto add_child(Statement const* child)
	  -> result::Result<Statement const*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto get_blocks() const -> Blocks const*;
	[[nodiscard]] auto add_block(Block const* block)
	  -> result::Result<Block const*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto get_parent() const -> Parent const*;
	[[nodiscard]] auto set_parent(Statement const* stmt)
	  -> result::Result<Statement const*, Failures::NO_RESOURCES, Failures::ALREADY_SETTED>;


private:
	Parent _parent;
	Blocks _blocks;
	Childs _childs;
};

}  // namespace domain::cfg
