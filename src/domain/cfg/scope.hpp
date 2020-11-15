#pragma once

#include <memory>
#include <vector>

#include "domain/cfg/block.hpp"

namespace cfg {

class Block;

//******************************************************************************
class Scope {
public:
	std::vector<Block*> blocks;
	std::vector<Scope*> childs;
	Scope* parent;

	Scope() = default;
};

} // namespace cfg
