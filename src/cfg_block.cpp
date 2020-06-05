#include "cfg_block.hpp"

using namespace std;
using namespace clang;

namespace cfg {

//******************************************************************************
Block::Block(CFGBlock& _block_clang, ASTContext& _context)
: block_clang(make_shared<CFGBlock>(_block_clang))
, context(_context)
{}

//******************************************************************************
void Block::append_successor(shared_ptr<Block> block) {
	successors.push_back(block);
	block->append_precedent(shared_ptr<Block>(this));
}

//******************************************************************************
void Block::append_precedent(shared_ptr<Block> block) {
	precedents.push_back(block);
	block->append_successor(shared_ptr<Block>(this));
}

//******************************************************************************
void Block::append_element(CFGElement element_clang, Element::Kind kind) {
	elements.push_back(make_shared<Element>(Element(element_clang, kind, context)));
	llvm::errs() << elements.back()->get_text() << "\n";
}

} // namespace cfg
