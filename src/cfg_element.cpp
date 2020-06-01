#include <clang/Lex/Lexer.h>

#include "cfg_element.hpp"

using namespace std;
using namespace clang;

//******************************************************************************
CfgElement::CfgElement(CFGElement& _element_clang, Kind _kind, ASTContext& _context)
: element_clang(make_shared<CFGElement>(_element_clang))
, kind(_kind)
, context(_context)
{}

//******************************************************************************
string CfgElement::get_text(void) {
	switch (kind) {
	case STATEMENT: {
		Stmt const* stmt = element_clang->getAs<CFGStmt>()->getStmt();
		if (stmt == nullptr)
			return "";

		bool invalid = false;
		StringRef src = Lexer::getSourceText(
			CharSourceRange::getTokenRange(stmt->getSourceRange()),
			context.getSourceManager(), context.getLangOpts(), &invalid);
		if (invalid)
			return "";

		return string(src);
		break;
	}
	case LOOP:
	case CONDITION:
	case SWITCH:
		break;
	}
}
