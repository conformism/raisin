#pragma once

#include <memory>
#include <vector>

#include "../block/block.hpp"
#include "../block/iblock.hpp"
#include "iscope.hpp"

namespace cfg {

using namespace core;

class Scope : public IScope<Scope, Block> {
private:
	// TODO(dauliac): check if there is way to put
	// it into const, and if we need to
	// add setter
	mutable Parent _parent;
	const Blocks _blocks;
	const Childs _childs;

public:
	auto get_blocks() const -> Blocks override;
	auto get_childs() const -> Childs override;
	auto get_parent() const -> Parent override;
};

}  // namespace cfg
