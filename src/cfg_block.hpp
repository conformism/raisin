#ifndef CFG_BLOCK_HPP
#define CFG_BLOCK_HPP

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Analysis/CFG.h>
REENABLE_WARNINGS

#include "cfg_element.hpp"

namespace cfg {

//******************************************************************************
class Block {
private:
	clang::ASTContext& context;

public:
	std::shared_ptr<clang::CFGBlock> block_clang;
	std::vector<std::shared_ptr<Block>> precedents;
	std::vector<std::shared_ptr<Block>> successors;
	std::vector<std::shared_ptr<Element>> elements;

	enum Kind {
		STATEMENT,
		LOOP,
		CONDITION,
		SWITCH
	} kind;
	bool is_entry;
	bool is_exit;

	Block(clang::CFGBlock& _block_clang, clang::ASTContext& _context);

	void append_successor(std::shared_ptr<Block> block);
	void append_precedent(std::shared_ptr<Block> block);
	void append_element(clang::CFGElement element_clang, Element::Kind kind);
};

} // namespace cfg

#endif // CFG_BLOCK_HPP
