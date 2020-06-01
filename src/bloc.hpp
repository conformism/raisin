#include <vector>

#include <clang/AST/Stmt.h>

#include "element.hpp"

class Bloc {
public:

	std::shared_ptr<Bloc> precedent;
	std::vector<std::shared_ptr<Bloc>> successors;
	std::vector<std::shared_ptr<Element>> elements;

	enum Kind {
		STATEMENT,
		LOOP,
		CONDITION,
		SWITCH
	} kind;

	Bloc(
		std::shared_ptr<Bloc> p,
		std::vector<std::shared_ptr<Bloc>> s,
		std::vector<std::shared_ptr<Element>> e)
	: precedent(p)
	, successors(s)
	, elements(e)
	{

	switch (begin(e)->statment->getStmtClass()) {
		case clang::IfStmt:
			this->kind = CONDITION;
			break;
		case clang::ForStmt:
			this->kind = LOOP;
			break;
		case clang::WhileStmt:
			this->kind = LOOP;
			break;
		case clang::SwitchStmt:
			this->kind = SWITCH;
			break;
		default:
			this->kind = STATEMENT;
	}}
};
