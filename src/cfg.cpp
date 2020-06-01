#include <clang/Lex/Lexer.h>

#include "cfg.hpp"

using namespace std;
using namespace clang;

//******************************************************************************
Cfg::Cfg(unique_ptr<CFG>& _cfg_clang, ASTContext& _context)
: cfg_clang(_cfg_clang)
, context(_context) {
	for (CFGBlock* block_clang : *cfg_clang) {
		llvm::errs() << block_clang->getBlockID() << "\n";

		bool newblock = false;
//		blocks.push_back(shared_ptr<CfgBlock>(new CfgBlock(*block_clang, context)));
//		shared_ptr<CfgBlock>& block = blocks.back();
		shared_ptr<CfgBlock> block;

		for (CFGElement element_clang : block_clang->Elements) {

/*			if (block_clang->getTerminator().isValid()) {
				Stmt const* stmt = block_clang->getTerminatorCondition(false);
				bool invalid = false;
				StringRef src = Lexer::getSourceText(
					CharSourceRange::getTokenRange(stmt->getSourceRange()),
					context.getSourceManager(), context.getLangOpts(), &invalid);
				llvm::errs() << "term : "
				             << block_clang->getTerminatorStmt()->getStmtClassName()
				             << " "
				             << src
//				             << block_clang->getTerminatorCondition(false)
				             << "\n";
			}
*/
			// Store only relevant elements
			switch (element_clang.getKind()) {
			case CFGElement::Kind::Statement:
			case CFGElement::Kind::CXXRecordTypedCall:
			case CFGElement::Kind::Constructor:
				// Ignore elements that are parts of terminator
				if (block_clang->getTerminator().isValid()
				&&  element_clang.getAs<CFGStmt>()->getStmt() == block_clang->getTerminatorCondition(false))
				//TODO add forStmt inc & cond
					continue;

				if (!newblock) {
					blocks.push_back(shared_ptr<CfgBlock>(new CfgBlock(*block_clang, context)));
					block = blocks.back();
					newblock = true;
				}
				block->append_element(element_clang, CfgElement::Kind::STATEMENT);
				break;
			}
		}

		// Store terminator in its own block

	}

	for (shared_ptr<CfgBlock> block : blocks) {
		llvm::errs() << "block\n";
		for (shared_ptr<CfgElement> element : block->elements) {
			llvm::errs() << "\telement\n";
			llvm::errs() << "\t" << element->get_text() << "\n";
		}
	}
}
