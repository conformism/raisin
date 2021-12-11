#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "domain/core/types.hpp"
#include "block.hpp"

namespace domain::cfg {

using namespace domain::core;

class Statement: core::Entity {
public:
	using Parent = Statement const*;
	using Blocks = domain::core::Aggregator<Block>;
	using Childs = domain::core::Aggregator<Statement>;

	[[nodiscard]] auto is_root() const -> bool;
	[[nodiscard]] auto has_childs() const -> bool;
	[[nodiscard]] auto get_blocks() const -> Blocks;
	[[nodiscard]] auto get_childs() const -> Childs;
	[[nodiscard]] auto get_parent() const -> Parent;

private:
	Parent _parent;
	Blocks _blocks;
	Childs _childs;
};

}  // namespace domain::cfg
