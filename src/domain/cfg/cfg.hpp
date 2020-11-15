#pragma once

#include <memory>
#include <vector>

#include "domain/cfg/block.hpp"
#include "domain/cfg/scope.hpp"

namespace cfg {

//******************************************************************************
class Cfg {
public:
	Element* element;
	std::vector<std::unique_ptr<Block>> blocks;
	std::vector<std::unique_ptr<Scope>> scopes;

	Cfg() = default;
};

} // namespace cfg