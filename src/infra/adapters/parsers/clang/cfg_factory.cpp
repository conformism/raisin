#include "cfg_factory.hpp"

using namespace std;
using namespace clang;

namespace infra::adapters::parser::clang {

unique_ptr<domain::cfg::Cfg const> build_cfg(ASTContext const& context, Stmt const* stmt) {
	static CfgFactory factory(context);
	return factory.build_cfg(stmt);
}

unique_ptr<domain::cfg::Cfg const> CfgFactory::build_cfg(Stmt const* stmt) {
	std::unique_ptr<domain::cfg::Block> block;
	std::unique_ptr<domain::cfg::Scope> scope;
	visit(stmt, block, scope);
	return make_unique<domain::cfg::Cfg const>(cfg());
}

CfgFactory::CfgFactory(ASTContext const& _context) : context(_context) {}

void CfgFactory::visit(
	Stmt const* stmt,
	std::unique_ptr<domain::cfg::Block>& newblock,
	std::unique_ptr<domain::cfg::Scope>& newscope) {
	if (stmt == nullptr) {
		newblock = nullptr;
		newscope = nullptr;
		return;
	}

	switch (stmt->getStmtClass()) {
		default: visit_stmt(stmt, newblock, newscope); break;
		case Stmt::CompoundStmtClass:
			// NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
			visit_compound_stmt(static_cast<CompoundStmt const*>(stmt), newblock, newscope);
			break;
	}
}

void CfgFactory::visit_stmt(
	Stmt const* stmt,
	std::unique_ptr<domain::cfg::Block>& newblock,
	std::unique_ptr<domain::cfg::Scope>& newscope) {}

void CfgFactory::visit_compound_stmt(
	CompoundStmt const* stmt,
	std::unique_ptr<domain::cfg::Block>& newblock,
	std::unique_ptr<domain::cfg::Scope>& newscope) {
	llvm::errs() << "{\n";
	//	newblock = nullptr;
	newscope = make_unique<domain::cfg::Scope>();

	for (CompoundStmt::const_reverse_body_iterator it = stmt->body_rbegin(),
	                                               end = stmt->body_rend();
	     it != end;
	     ++it) {
		std::unique_ptr<domain::cfg::Block> block;
		std::unique_ptr<domain::cfg::Scope> scope;
		visit(*it, block, scope);
		if (scope != nullptr) {
			scope->parent = newscope.get();
			newscope->childs.push_back(scope.get());
		}
		if (block != nullptr) {
			block->scope = newscope.get();
			newscope->blocks.push_back(block.get());
		}
	}
	// TODO(thomaslepoix): last (first in reverse order) = newblock ?
	llvm::errs() << "}\n";
}

}  // namespace infra::adapters::parser::clang
