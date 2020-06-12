#ifndef CFG_BUILDER_HPP
#define CFG_BUILDER_HPP

#include <memory>

#include "cfg.hpp"

namespace cfg {

//******************************************************************************
std::unique_ptr<Cfg> build_cfg(clang::Stmt const* stmt);

//******************************************************************************
class Builder {
private:
	//TODO Block* vs Scope* return type
	void visit(clang::Stmt const* stmt, Block* newblock, Scope* newscope);
	void visit_stmt(clang::Stmt const* stmt, Block* newblock, Scope* newscope);
	void visit_compound_stmt(clang::CompoundStmt const* stmt, Block* newblock, Scope* newscope);
	void visit_for_stmt(clang::ForStmt const* stmt, Block* newblock, Scope* newscope);
	void visit_if_stmt(clang::IfStmt const* stmt, Block* newblock, Scope* newscope);
	void visit_while_stmt(clang::WhileStmt const* stmt, Block* newblock, Scope* newscope);

	Builder(void) = default;
	std::unique_ptr<Cfg> build_cfg(clang::Stmt const* stmt);
	friend std::unique_ptr<Cfg> build_cfg(clang::Stmt const* stmt);
};

} // namespace cfg

#endif // CFG_BUILDER_HPP
