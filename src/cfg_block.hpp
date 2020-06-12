#ifndef CFG_BLOCK_HPP
#define CFG_BLOCK_HPP

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

#include "cfg_element.hpp"
#include "cfg_scope.hpp"

namespace cfg {

class Scope;

//******************************************************************************
class Block {
private:
	clang::ASTContext& context;

public:
	Scope* scope;
	std::vector<Block*> precedents;
	std::vector<Block*> successors;
	std::vector<std::unique_ptr<Element>> elements;

	enum Kind {
		STATEMENT,
		LOOP,
		CONDITION,
		SWITCH
	} kind;
	bool is_entry;
	bool is_exit;

	Block(clang::ASTContext& _context);

	void append_successor(Block* block);
	void append_precedent(Block* block);
	void append_element(clang::Stmt const* stmt);
};

} // namespace cfg

#endif // CFG_BLOCK_HPP
