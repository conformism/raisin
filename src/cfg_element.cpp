#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Lex/Lexer.h>
REENABLE_WARNINGS

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
	case LOOP: {
		Stmt const* stmt = element_clang->getAs<CFGStmt>()->getStmt();
		if (stmt == nullptr)
			return "";

		if (stmt->getStmtClass() == Stmt::WhileStmtClass) {
			return "WHILE";
		} else if (stmt->getStmtClass() == Stmt::DoStmtClass) {
			return "DO";
		} else if (stmt->getStmtClass() == Stmt::ForStmtClass) {
			ForStmt const* for_stmt = static_cast<ForStmt const*>(stmt); //TODO is valid?

			bool invalid = false;
			StringRef src = Lexer::getSourceText(
				CharSourceRange::getTokenRange(SourceRange(for_stmt->getLParenLoc(), for_stmt->getRParenLoc())),
				context.getSourceManager(), context.getLangOpts(), &invalid);
			if (invalid)
				return "";

			return string(src);
		}
		break;
	}
	case CONDITION: {
		Stmt const* stmt = element_clang->getAs<CFGStmt>()->getStmt();
		if (stmt == nullptr)
			return "";

		if (stmt->getStmtClass() == Stmt::IfStmtClass) {
			return "IF";
		}
		break;
	}
	case SWITCH:
		break;
	}
}