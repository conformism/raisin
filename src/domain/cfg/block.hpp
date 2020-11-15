#pragma once

#include <memory>
#include <string>
#include <vector>

#include "domain/cfg/element.hpp"
#include "domain/cfg/scope.hpp"

namespace cfg {

class Scope;

//******************************************************************************
class Block {
public:
	Scope* scope;
	std::vector<Block*> precedents;
	std::vector<Block*> successors;
	std::vector<std::unique_ptr<Element>> elements;

	enum Kind {
		STATEMENT,
		LOOP,
		CONDITION,
		SWITCH,
		FUNCTION
	} kind;
	bool is_entry;
	bool is_exit;

	Block(Kind const _kind);
	std::string get_text() const;
};

} // namespace cfg
