#pragma once

#include <memory>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

#include "domain/factories/cfg/wip_cfg.hpp"

namespace cfg {

//******************************************************************************
std::unique_ptr<Cfg> build_cfg(clang::ASTContext& context, clang::Stmt const* stmt);

//******************************************************************************
class Builder {
private:
	clang::ASTContext& context;
	Cfg cfg;

	//TODO Block* vs Scope* return type
	//TODO current scope, last/first block
	void visit(clang::Stmt const* stmt, Block* newblock, Scope* newscope);
	void visit_stmt(clang::Stmt const* stmt, Block* newblock, Scope* newscope);
	void visit_compound_stmt(clang::CompoundStmt const* stmt, Block* newblock, Scope* newscope);
	void visit_for_stmt(clang::ForStmt const* stmt, Block* newblock, Scope* newscope);
	void visit_if_stmt(clang::IfStmt const* stmt, Block* newblock, Scope* newscope);
	void visit_while_stmt(clang::WhileStmt const* stmt, Block* newblock, Scope* newscope);

	Builder(clang::ASTContext& _context, clang::Stmt const* stmt);
	std::unique_ptr<Cfg> build_cfg(clang::Stmt const* stmt);
	friend std::unique_ptr<Cfg> build_cfg(clang::ASTContext& context, clang::Stmt const* stmt);
};

} // namespace cfg
