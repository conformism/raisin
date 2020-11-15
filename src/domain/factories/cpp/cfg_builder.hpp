#pragma once

#include <memory>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

#include "domain/cfg/cfg.hpp"

namespace cfg {

//******************************************************************************
std::unique_ptr<Cfg const> build_cfg(clang::ASTContext const& context, clang::Stmt const* stmt);

//******************************************************************************
class Builder {
private:
	clang::ASTContext const& context;
	Cfg cfg;

	//TODO Block* vs Scope* return type
	//TODO current scope, last/first block
	void visit(clang::Stmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope);
	void visit_stmt(clang::Stmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope);
	void visit_compound_stmt(clang::CompoundStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope);
	void visit_for_stmt(clang::ForStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope);
	void visit_if_stmt(clang::IfStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope);
	void visit_while_stmt(clang::WhileStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope);

	Builder(clang::ASTContext const& _context);
	std::unique_ptr<Cfg const> build_cfg(clang::Stmt const* stmt);
	friend std::unique_ptr<Cfg const> build_cfg(clang::ASTContext const& context, clang::Stmt const* stmt);
};

} // namespace cfg
