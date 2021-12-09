#include "cfg_factory.hpp"

using namespace std;

namespace infra::services::parser::clang {

using namespace ::clang;
using namespace domain::cfg;

unique_ptr<Cfg const> build_cfg(ASTContext const& context, Stmt const* stmt) {
	static CfgFactory factory(context);
	return factory.build_cfg(stmt);
}

unique_ptr<Cfg const> CfgFactory::build_cfg(Stmt const* stmt) {
	std::unique_ptr<Block::Builder> block;
	std::unique_ptr<Scope::Builder> scope;
	visit(stmt, block, scope);
//	return make_unique<Cfg const>(cfg());
}

CfgFactory::CfgFactory(ASTContext const& _context)
: context(_context)
//, cfg()
, cfg_builder()
{}

void CfgFactory::visit(
	Stmt const* stmt,
	std::unique_ptr<Block::Builder>& newblock,
	std::unique_ptr<Scope::Builder>& newscope) {
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
		cfg_builder.blocks.push_back(unique_ptr<Block::Builder>(newblock.release()));
	if (newscope != nullptr)
		cfg_builder.scopes.push_back(unique_ptr<Scope::Builder>(newscope.release()));
}

//******************************************************************************
void CfgFactory::visit_stmt(
	Stmt const* stmt,
	std::unique_ptr<Block::Builder>& newblock,
	std::unique_ptr<Scope::Builder>& newscope)
{}

//******************************************************************************
void CfgFactory::visit_compound_stmt(
	CompoundStmt const* stmt,
	std::unique_ptr<Block::Builder>& newblock,
	std::unique_ptr<Scope::Builder>& newscope)
{
	llvm::errs() << "{\n";
//	newblock = nullptr;
	newscope = make_unique<Scope::Builder>();
	for (CompoundStmt::const_reverse_body_iterator it=stmt->body_rbegin(), end=stmt->body_rend(); it != end; ++it) {
		std::unique_ptr<Block::Builder> block;
		std::unique_ptr<Scope::Builder> scope;
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
void CfgFactory::visit_for_stmt(ForStmt const* stmt, std::unique_ptr<Block::Builder>& newblock, std::unique_ptr<Scope::Builder>& newscope) {
}

//******************************************************************************
void CfgFactory::visit_if_stmt(IfStmt const* stmt, std::unique_ptr<Block::Builder>& newblock, std::unique_ptr<Scope::Builder>& newscope) {
	newblock = make_unique<Block::Builder>(Block::Kind::CONDITION);
	newblock->elements.push_back(make_unique<WipElement>(context, stmt->getCond()));
	{
		std::unique_ptr<Block::Builder> block;
		std::unique_ptr<Scope::Builder> scope;
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
		std::unique_ptr<Block::Builder> block;
		std::unique_ptr<Scope::Builder> scope;
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
void CfgFactory::visit_while_stmt(WhileStmt const* stmt, std::unique_ptr<Block::Builder>& newblock, std::unique_ptr<Scope::Builder>& newscope) {
}

}  // namespace infra::services::parser::clang
