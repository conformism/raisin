#ifndef CFG_HPP
#define CFG_HPP

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Analysis/CFG.h>
REENABLE_WARNINGS

#include "cfg_block.hpp"

//******************************************************************************
class Cfg {
private:
	clang::ASTContext& context;

public:
	std::unique_ptr<clang::CFG>& cfg_clang;
	std::vector<std::shared_ptr<CfgBlock>> blocks;

	Cfg(std::unique_ptr<clang::CFG>& _cfg_clang, clang::ASTContext& _context);
};

#endif // CFG_HPP
