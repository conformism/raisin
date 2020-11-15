#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Lex/Lexer.h>
REENABLE_WARNINGS

#include "domain/factories/cpp/wip_element.hpp"

using namespace std;
using namespace clang;

namespace cfg {

//******************************************************************************
WipElement::WipElement(ASTContext const& context, Stmt const* stmt)
: Element(std::move(get_str(context, stmt)))
{}

//******************************************************************************
string WipElement::get_str(ASTContext const& context, Stmt const* stmt) const {
	if (stmt == nullptr)
		return "";

	bool invalid = false;
	StringRef src;

	switch (stmt->getStmtClass()) {
	default: {
		src = Lexer::getSourceText(
			CharSourceRange::getTokenRange(stmt->getSourceRange()),
			context.getSourceManager(), context.getLangOpts(), &invalid);
		break;
	} case Stmt::WhileStmtClass: {
		return "WHILE";
		break;
	} case Stmt::DoStmtClass: {
		return "DO";
		break;
	} case Stmt::ForStmtClass: {
		ForStmt const* for_stmt = static_cast<ForStmt const*>(stmt); //TODO is valid?

		src = Lexer::getSourceText(
			CharSourceRange::getTokenRange(SourceRange(for_stmt->getLParenLoc(), for_stmt->getRParenLoc())),
			context.getSourceManager(), context.getLangOpts(), &invalid);
		break;
	} case Stmt::IfStmtClass: {
			return "IF";
		break;
	}
	}

	return (invalid ? "" : string(src));
}

} // namespace cfg
