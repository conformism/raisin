#include "cfg_builder.hpp"

using namespace std;
using namespace clang;

namespace cfg {

//******************************************************************************
unique_ptr<Cfg> build_cfg(ASTContext& context, Stmt const* stmt) {
	Builder builder(context, stmt);
	return builder.build_cfg(stmt);
}

//******************************************************************************
unique_ptr<Cfg> Builder::build_cfg(Stmt const* stmt) {
	Block* block;
	Scope* scope;
	visit(stmt, block, scope);
	return make_unique<Cfg>(std::move(cfg));
}

//******************************************************************************
Builder::Builder(ASTContext& _context, Stmt const* stmt)
: context(_context)
, cfg(_context, stmt)
{}

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
		cfg.blocks.push_back(unique_ptr<Block>(newblock));
	if (newscope != nullptr)
		cfg.scopes.push_back(unique_ptr<Scope>(newscope));
}

//******************************************************************************
void Builder::visit_stmt(Stmt const* stmt, Block* newblock, Scope* newscope) {
}

//******************************************************************************
void Builder::visit_compound_stmt(clang::CompoundStmt const* stmt, Block* newblock, Scope* newscope) {
	llvm::errs() << "{\n";
	newblock = nullptr;
	newscope = new Scope(context);
	for (CompoundStmt::const_reverse_body_iterator it=stmt->body_rbegin(), end=stmt->body_rend(); it != end; ++it) {
		Block* block;
		Scope* scope;
		visit(*it, block, scope);
		if (scope != nullptr) {
			scope->parent = newscope;
			newscope->childs.push_back(scope);
		}
		if (block != nullptr) {
			block->scope = newscope;
			newscope->blocks.push_back(block);
		}
	}
	llvm::errs() << "}\n";
}

//******************************************************************************
void Builder::visit_for_stmt(ForStmt const* stmt, Block* newblock, Scope* newscope) {
}

//******************************************************************************
void Builder::visit_if_stmt(IfStmt const* stmt, Block* newblock, Scope* newscope) {
	newblock = new Block(context);
	newblock->kind = Block::Kind::CONDITION;
	newblock->elements.push_back(make_unique<Element>(context, stmt->getCond()));
	{
		Block* block;
		Scope* scope;
		visit(stmt->getThen(), block, scope);
		if (scope != nullptr) {
			scope->parent = newblock->scope; //TODO block <-> block link
		}
		if (block != nullptr) {
			block->precedents.push_back(newblock);
			newblock->successors.push_back(block);
		}
	}
	{
		Block* block;
		Scope* scope;
		visit(stmt->getElse(), block, scope);
		if (scope != nullptr) {
			scope->parent = newblock->scope; //TODO block <-> block link
		}
		if (block != nullptr) {
			block->precedents.push_back(newblock);
			newblock->successors.push_back(block);
		}
	}
}

//******************************************************************************
void Builder::visit_while_stmt(WhileStmt const* stmt, Block* newblock, Scope* newscope) {
}

} // namespace cfg
