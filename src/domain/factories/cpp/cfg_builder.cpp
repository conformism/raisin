#include "domain/factories/cpp/wip_element.hpp"
#include "domain/factories/cpp/cfg_builder.hpp"

using namespace std;
using namespace clang;

namespace cfg {

//******************************************************************************
unique_ptr<Cfg const> build_cfg(ASTContext const& context, Stmt const* stmt) {
	Builder builder(context);
	return builder.build_cfg(stmt);
}

//******************************************************************************
unique_ptr<Cfg const> Builder::build_cfg(Stmt const* stmt) {
	std::unique_ptr<Block> block;
	std::unique_ptr<Scope> scope;
	visit(stmt, block, scope);
	return make_unique<Cfg const>(std::move(cfg));
}

//******************************************************************************
Builder::Builder(ASTContext const& _context)
: context(_context)
, cfg()
{}

//******************************************************************************
void Builder::visit(Stmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope) {
	if (stmt == nullptr) {
		newblock = nullptr;
		newscope = nullptr;
		return;
	}

	switch (stmt->getStmtClass()) {
	default:
		visit_stmt(stmt, newblock, newscope);
		break;
	case Stmt::CompoundStmtClass:
		visit_compound_stmt(static_cast<CompoundStmt const*>(stmt), newblock, newscope);
		break;
	case Stmt::ForStmtClass:
		visit_for_stmt(static_cast<ForStmt const*>(stmt), newblock, newscope);
		break;
	case Stmt::IfStmtClass:
		visit_if_stmt(static_cast<IfStmt const*>(stmt), newblock, newscope);
		break;
	case Stmt::WhileStmtClass:
		visit_while_stmt(static_cast<WhileStmt const*>(stmt), newblock, newscope);
		break;
	}

	if (newblock != nullptr)
		cfg.blocks.push_back(unique_ptr<Block>(newblock.release()));
	if (newscope != nullptr)
		cfg.scopes.push_back(unique_ptr<Scope>(newscope.release()));
}

//******************************************************************************
void Builder::visit_stmt(Stmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope) {
}

//******************************************************************************
void Builder::visit_compound_stmt(clang::CompoundStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope) {
	llvm::errs() << "{\n";
//	newblock = nullptr;
	newscope = make_unique<Scope>();
	for (CompoundStmt::const_reverse_body_iterator it=stmt->body_rbegin(), end=stmt->body_rend(); it != end; ++it) {
		std::unique_ptr<Block> block;
		std::unique_ptr<Scope> scope;
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
	// TODO: last (first in reverse order) = newblock ?
	llvm::errs() << "}\n";
}

//******************************************************************************
void Builder::visit_for_stmt(ForStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope) {
}

//******************************************************************************
void Builder::visit_if_stmt(IfStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope) {
	newblock = make_unique<Block>(Block::Kind::CONDITION);
	newblock->elements.push_back(make_unique<WipElement>(context, stmt->getCond()));
	{
		std::unique_ptr<Block> block;
		std::unique_ptr<Scope> scope;
		visit(stmt->getThen(), block, scope);
		if (scope != nullptr) {
			scope->parent = newblock->scope; //TODO block <-> block link
		}
		if (block != nullptr) {
			block->precedents.push_back(newblock.get());
			newblock->successors.push_back(block.get());
		}
	}
	{
		std::unique_ptr<Block> block;
		std::unique_ptr<Scope> scope;
		visit(stmt->getElse(), block, scope);
		if (scope != nullptr) {
			scope->parent = newblock->scope; //TODO block <-> block link
		}
		if (block != nullptr) {
			block->precedents.push_back(newblock.get());
			newblock->successors.push_back(block.get());
		}
	}
}

//******************************************************************************
void Builder::visit_while_stmt(WhileStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<Scope>& newscope) {
}

} // namespace cfg
