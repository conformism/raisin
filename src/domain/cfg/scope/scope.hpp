#pragma once

#include <memory>
#include <vector>

#include "iscope.hpp"
#include "../block/iblock.hpp"

namespace cfg {

class Scope: public IScope {
private:
	const Uuid _uuid;
	//TODO: check if there is way to put
	// it into const, and if we need to
	// add setter
	mutable Parent _parent;
	const Blocks _blocks;
	const Childs _childs;

public:
	IBlock::Uuid get_uuid() const override;
	Blocks get_blocks() const override;
	Childs get_childs() const override;
	Parent get_parent() const override;
};

} // namespace cfg
