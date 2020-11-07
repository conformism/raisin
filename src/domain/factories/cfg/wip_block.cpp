#include "domain/factories/cfg/wip_block.hpp"

using namespace std;
using namespace clang;

namespace cfg {

//******************************************************************************
WipBlock::WipBlock(clang::ASTContext& _context)
: Block(_context)
{}

//******************************************************************************
void WipBlock::append_successor(WipBlock* wip_block) {
	successors.push_back(wip_block);
	wip_block->append_precedent(this);
}

//******************************************************************************
void WipBlock::append_precedent(WipBlock* wip_block) {
	precedents.push_back(wip_block);
	wip_block->append_successor(this);
}

//******************************************************************************
void WipBlock::append_element(clang::Stmt const* stmt) {
	elements.push_back(make_unique<WipElement>(context, stmt));
	// TODO: REMOVE IT
	llvm::errs() << static_cast<WipElement*>(elements.back().get())->get_text() << "\n";
}

} // namespace cfg
