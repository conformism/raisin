#pragma once

#include "domain/factories/cfg/wip_block.hpp"
#include "domain/cfg/scope.hpp"

namespace cfg {

class Block;

//******************************************************************************
class WipScope : public Scope {
public:
	WipScope(clang::ASTContext& _context);
};

} // namespace cfg
