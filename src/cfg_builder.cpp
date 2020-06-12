#include "cfg_builder.hpp"

using namespace std;
using namespace clang;

namespace cfg {

//******************************************************************************
unique_ptr<Cfg> build_cfg(Stmt const* stmt) {
	Builder builder;
	return builder.build_cfg(stmt);
}

//******************************************************************************
unique_ptr<Cfg> Builder::build_cfg(Stmt const* stmt) {
	Block* block;
	Scope* scope;
	visit(stmt, block, scope);
}

//******************************************************************************
void Builder::visit(Stmt const* stmt, Block* newblock, Scope* newscope) {
	if (stmt == nullptr) {
		newblock = nullptr;
		newscope = nullptr;
		return;
	}

	switch (stmt->getStmtClass()) {
	default:
		visit_stmt(stmt, newblock, newscope);
		return;
	case Stmt::CompoundStmtClass:
		visit_compound_stmt(static_cast<CompoundStmt const*>(stmt), newblock, newscope);
		return;
	case Stmt::ForStmtClass:
		visit_for_stmt(static_cast<ForStmt const*>(stmt), newblock, newscope);
		return;
	case Stmt::IfStmtClass:
		visit_if_stmt(static_cast<IfStmt const*>(stmt), newblock, newscope);
		return;
	case Stmt::WhileStmtClass:
		visit_while_stmt(static_cast<WhileStmt const*>(stmt), newblock, newscope);
		return;
	}
}

//******************************************************************************
void Builder::visit_stmt(Stmt const* stmt, Block* newblock, Scope* newscope) {
}

//******************************************************************************
void Builder::visit_compound_stmt(clang::CompoundStmt const* stmt, Block* newblock, Scope* newscope) {
	llvm::errs() << "{\n";
	for (CompoundStmt::const_reverse_body_iterator it=stmt->body_rbegin(), end=stmt->body_rend(); it != end; ++it ) {
		Block* block;
		Scope* scope;
		visit(*it, block, scope);
	}
	llvm::errs() << "}\n";
}

//******************************************************************************
void Builder::visit_for_stmt(ForStmt const* stmt, Block* newblock, Scope* newscope) {
}

//******************************************************************************
void Builder::visit_if_stmt(IfStmt const* stmt, Block* newblock, Scope* newscope) {
}

//******************************************************************************
void Builder::visit_while_stmt(WhileStmt const* stmt, Block* newblock, Scope* newscope) {
}

} // namespace cfg
