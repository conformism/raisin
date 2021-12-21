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
	auto [block, scope] = visit(stmt);
//	return make_unique<Cfg const>(cfg());
}

CfgFactory::CfgFactory(ASTContext const& _context)
: context(_context)
//, cfg()
, cfg()
{}

auto CfgFactory::visit(Stmt const* stmt) -> std::tuple<Block*, CompoundStatement*>
{
	if (!stmt)
		return { nullptr, nullptr };

	auto [newblock, newscope] = [&] {
		switch (stmt->getStmtClass()) {
		default:
			return visit_stmt(stmt);
		case Stmt::CompoundStmtClass:
			return visit_compound_stmt(static_cast<CompoundStmt const*>(stmt));
		case Stmt::ForStmtClass:
			return visit_for_stmt(static_cast<ForStmt const*>(stmt));
		case Stmt::IfStmtClass:
			return visit_if_stmt(static_cast<IfStmt const*>(stmt));
		case Stmt::WhileStmtClass:
			return visit_while_stmt(static_cast<WhileStmt const*>(stmt));
		}
	} ();

	Block* newblock_ptr = nullptr;
	CompoundStatement* newscope_ptr = nullptr;

	if (newblock) {
		newblock_ptr = newblock.get();
		cfg.add_block(move(newblock));
	}
	if (newscope) {
		newscope_ptr = newscope.get();
		cfg.add_compound_statement(move(newscope));
	}

	return { newblock_ptr, newscope_ptr };
}

auto CfgFactory::visit_stmt(Stmt const* stmt) -> CfgFactory::VisitorRet {}

auto CfgFactory::visit_compound_stmt(CompoundStmt const* stmt) -> CfgFactory::VisitorRet
{
	llvm::errs() << "{\n";
	auto newscope = make_unique<CompoundStatement>();
	for (CompoundStmt::const_reverse_body_iterator it = stmt->body_rbegin(), end = stmt->body_rend(); it != end; ++it) {
		auto [block, scope] = visit(*it);
		if (scope) {
			scope->set_parent(newscope.get());
			newscope->add_child(scope);
		}
		if (block) {
			block->set_scope(scope);
			newscope->add_child(scope);
		}
	}
	// TODO: last (first in reverse order) = newblock ?
	llvm::errs() << "}\n";
	return { nullptr, move(newscope) };
}

auto CfgFactory::visit_for_stmt(ForStmt const* stmt) -> CfgFactory::VisitorRet {}

auto CfgFactory::visit_if_stmt(IfStmt const* stmt) -> CfgFactory::VisitorRet
{
	auto newblock = make_unique<Block>(Block::Kind::CONDITION);
//	newblock->elements.push_back(make_unique<Element>(context, stmt->getCond()));
	newblock->add_element(make_unique<Element>(context, stmt->getCond()));
//	newblock->add_element(Element(context, stmt->getCond()));
	{
		auto [block, scope] = visit(stmt->getThen());
		if (scope) {
			scope->set_parent(newblock->get_scope()); //TODO block <-> block link
		}
		if (block) {
			block->set_precedent(newblock.get());
			newblock->add_successor(block);
		}
	}
	{
		auto [block, scope] = visit(stmt->getElse());
		if (scope) {
			scope->set_parent(newblock->get_scope()); //TODO block <-> block link
		}
		if (block) {
			block->set_precedent(newblock.get());
			newblock->add_successor(block);
		}
	}
	return { move(newblock), nullptr };
}

auto CfgFactory::visit_while_stmt(WhileStmt const* stmt) -> CfgFactory::VisitorRet {}

/*
void CfgFactory::visit(
	Stmt const* stmt,
	std::unique_ptr<Block>& newblock,
	std::unique_ptr<CompoundStatement>& newscope) {
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

	// TODO why???
	if (newblock != nullptr)
		cfg.blocks.push_back(unique_ptr<Block>(newblock.release()));
	if (newscope != nullptr)
		cfg.scopes.push_back(unique_ptr<CompoundStatement>(newscope.release()));
}

//******************************************************************************
void CfgFactory::visit_stmt(
	Stmt const* stmt,
	std::unique_ptr<Block>& newblock,
	std::unique_ptr<CompoundStatement>& newscope)
{}

//******************************************************************************
void CfgFactory::visit_compound_stmt(
	CompoundStmt const* stmt,
	std::unique_ptr<Block>& newblock,
	std::unique_ptr<CompoundStatement>& newscope)
{
	llvm::errs() << "{\n";
//	newblock = nullptr;
	newscope = make_unique<CompoundStatement>();
	for (CompoundStmt::const_reverse_body_iterator it=stmt->body_rbegin(), end=stmt->body_rend(); it != end; ++it) {
		std::unique_ptr<Block> block;
		std::unique_ptr<CompoundStatement> scope;
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
void CfgFactory::visit_for_stmt(ForStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<CompoundStatement>& newscope) {
}

//******************************************************************************
void CfgFactory::visit_if_stmt(IfStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<CompoundStatement>& newscope) {
	newblock = make_unique<Block>(Block::Kind::CONDITION);
	newblock->elements.push_back(make_unique<WipElement>(context, stmt->getCond()));
	{
		std::unique_ptr<Block> block;
		std::unique_ptr<CompoundStatement> scope;
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
		std::unique_ptr<CompoundStatement> scope;
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
void CfgFactory::visit_while_stmt(WhileStmt const* stmt, std::unique_ptr<Block>& newblock, std::unique_ptr<CompoundStatement>& newscope) {
}
*/

}  // namespace infra::services::parser::clang
