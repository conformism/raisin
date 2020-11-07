#pragma once

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

#include "domain/cfg/block.hpp"

namespace cfg {

class Block;

//******************************************************************************
class Scope {
protected:
	clang::ASTContext& context;

public:
	std::vector<Block*> blocks;
	std::vector<Scope*> childs;
	Scope* parent;

	Scope(clang::ASTContext& _context);
};

} // namespace cfg
