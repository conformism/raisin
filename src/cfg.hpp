#ifndef CFG_HPP
#define CFG_HPP

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

#include "cfg_block.hpp"
#include "cfg_scope.hpp"

namespace cfg {

//******************************************************************************
class Cfg {
private:
	clang::ASTContext& context;
	clang::Stmt const* stmt;

public:
	std::vector<std::unique_ptr<Block>> blocks;
	std::vector<std::unique_ptr<Scope>> scopes;

	Cfg(clang::ASTContext& _context, clang::Stmt const* _stmt);
};

} // namespace cfg

#endif // CFG_HPP
