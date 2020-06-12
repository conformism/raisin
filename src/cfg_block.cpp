#include "cfg_block.hpp"

using namespace std;
using namespace clang;

namespace cfg {

//******************************************************************************
Block::Block(ASTContext& _context)
: context(_context)
{}

//******************************************************************************
void Block::append_successor(Block* block) {
	successors.push_back(block);
	block->append_precedent(this);
}

//******************************************************************************
void Block::append_precedent(Block* block) {
	precedents.push_back(block);
	block->append_successor(this);
}

//******************************************************************************
void Block::append_element(clang::Stmt const* stmt) {
	elements.push_back(make_unique<Element>(Element(context, stmt)));
	llvm::errs() << elements.back()->get_text() << "\n";
}

} // namespace cfg
