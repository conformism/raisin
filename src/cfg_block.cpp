#include "cfg_block.hpp"

using namespace std;
using namespace clang;

CfgBlock::CfgBlock(CFGBlock& _block_clang, ASTContext& _context)
: block_clang(make_shared<CFGBlock>(_block_clang))
, context(_context)
{}

void CfgBlock::append_element(CFGElement element_clang, CfgElement::Kind kind) {
	elements.push_back(shared_ptr<CfgElement>(new CfgElement(element_clang, kind, context)));
	llvm::errs() << elements.back()->get_text() << "\n";
}
