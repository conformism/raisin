#pragma once

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

#include "domain/cfg/block.hpp"
#include "domain/cfg/scope.hpp"

namespace cfg {

//******************************************************************************
class Cfg {
protected:
	clang::ASTContext& context;
	clang::Stmt const* stmt;

public:
	std::vector<std::unique_ptr<Block>> blocks;
	std::vector<std::unique_ptr<Scope>> scopes;

	Cfg(clang::ASTContext& _context, clang::Stmt const* _stmt);
};

} // namespace cfg