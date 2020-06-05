#ifndef CFG_SCOPE_HPP
#define CFG_SCOPE_HPP

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Analysis/CFG.h>
REENABLE_WARNINGS

#include "cfg_block.hpp"

namespace cfg {

//******************************************************************************
class Scope {
private:
	clang::ASTContext& context;

public:
	std::vector<std::shared_ptr<CfgBlock>> blocks;
	std::vector<std::shared_ptr<CfgScope>> childs;
	shared_ptr<CfgScope> parent;

	Scope(clang::ASTContext& _context);
};

} // namespace cfg

#endif // CFG_SCOPE_HPP
