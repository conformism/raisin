#ifndef CFG_BLOCK_HPP
#define CFG_BLOCK_HPP

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Analysis/CFG.h>
REENABLE_WARNINGS

#include "cfg_element.hpp"

//******************************************************************************
class CfgBlock {
private:
	clang::ASTContext& context;

public:
	std::shared_ptr<clang::CFGBlock> block_clang;
	std::vector<std::shared_ptr<CfgElement>> elements;

	CfgBlock(clang::CFGBlock& _block_clang, clang::ASTContext& _context);

	void append_element(clang::CFGElement element_clang, CfgElement::Kind kind);
};

#endif // CFG_BLOCK_HPP
