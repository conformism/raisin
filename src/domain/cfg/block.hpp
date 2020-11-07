#pragma once

#include <memory>
#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

#include "domain/cfg/element.hpp"
#include "domain/cfg/scope.hpp"

namespace cfg {

class Scope;

//******************************************************************************
class Block {
protected:
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
};

} // namespace cfg
