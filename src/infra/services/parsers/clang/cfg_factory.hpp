#pragma once

#include <memory>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include "clang/AST/AST.h"
REENABLE_WARNINGS

#include "domain/cfg/cfg.hpp"

namespace infra::services::parser::clang {

//******************************************************************************
std::unique_ptr<domain::cfg::Cfg const> build_cfg(
	::clang::ASTContext const& context,
	::clang::Stmt const* stmt);

//******************************************************************************
class CfgFactory {
private:
	::clang::ASTContext const& context;
//	domain::cfg::Cfg cfg;
	domain::cfg::Cfg::Builder cfg_builder;

	// TODO(thomaslepoix) Block* vs Scope* return type
	// TODO(thomaslepoix) current scope, last/first block
	void visit(
		::clang::Stmt const* stmt,
		std::unique_ptr<domain::cfg::Block::Builder>& newblock,
		std::unique_ptr<domain::cfg::Scope::Builder>& newscope);
	void visit_stmt(
		::clang::Stmt const* stmt,
		std::unique_ptr<domain::cfg::Block::Builder>& newblock,
		std::unique_ptr<domain::cfg::Scope::Builder>& newscope);
	void visit_compound_stmt(
		::clang::CompoundStmt const* stmt,
		std::unique_ptr<domain::cfg::Block::Builder>& newblock,
		std::unique_ptr<domain::cfg::Scope::Builder>& newscope);
	void visit_for_stmt(
		::clang::ForStmt const* stmt,
		std::unique_ptr<domain::cfg::Block::Builder>& newblock,
		std::unique_ptr<domain::cfg::Scope::Builder>& newscope);
	void visit_if_stmt(
		::clang::IfStmt const* stmt,
		std::unique_ptr<domain::cfg::Block::Builder>& newblock,
		std::unique_ptr<domain::cfg::Scope::Builder>& newscope);
	void visit_while_stmt(
		::clang::WhileStmt const* stmt,
		std::unique_ptr<domain::cfg::Block::Builder>& newblock,
		std::unique_ptr<domain::cfg::Scope::Builder>& newscope);

	explicit CfgFactory(::clang::ASTContext const& _context);

	std::unique_ptr<domain::cfg::Cfg const> build_cfg(::clang::Stmt const* stmt);

	friend std::unique_ptr<domain::cfg::Cfg const> build_cfg(
		::clang::ASTContext const& context,
		::clang::Stmt const* stmt);
};

}  // namespace infra::services::parser::clang
