#ifndef CFG_SCOPE_HPP
#define CFG_SCOPE_HPP

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

#include "cfg_block.hpp"

namespace cfg {

class Block;

//******************************************************************************
class Scope {
private:
	clang::ASTContext& context;

public:
	std::vector<Block*> blocks;
	std::vector<Scope*> childs;
	Scope* parent;

	Scope(clang::ASTContext& _context);
};

} // namespace cfg

#endif // CFG_SCOPE_HPP
