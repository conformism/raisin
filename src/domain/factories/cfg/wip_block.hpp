#pragma once

#include "domain/factories/cfg/wip_element.hpp"
#include "domain/factories/cfg/wip_scope.hpp"
#include "domain/cfg/block.hpp"

namespace cfg {

class Scope;

//******************************************************************************
class WipBlock : public Block {
public:
	WipBlock(clang::ASTContext& _context);

	void append_successor(WipBlock* wip_block);
	void append_precedent(WipBlock* wip_block);
	void append_element(clang::Stmt const* stmt);
};

} // namespace cfg
