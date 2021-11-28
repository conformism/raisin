#include <sstream>
#include <string>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Analysis/CFG.h>
#include <clang/Basic/LangOptions.h>
#include <llvm/Support/raw_ostream.h>
REENABLE_WARNINGS

#include "domain/factories/cpp/ast_processor.hpp"
#include "domain/factories/cpp/cfg_builder.hpp"

using namespace clang;
// using namespace cfg;

//******************************************************************************
ast_visitor::ast_visitor(ASTContext& c) : context(c) {}

//******************************************************************************
bool AstVisitor::VisitFunctionDecl(FunctionDecl* f) {
	// TODO
	bool const is_in_system_header =
		context.getSourceManager().isInSystemHeader(f->getSourceRange().getBegin())
		|| context.getSourceManager().isInSystemHeader(f->getSourceRange().getEnd())
		|| (f->isTemplateInstantiation()
	        && context.getSourceManager().isInSystemHeader(f->getPointOfInstantiation()));
	if (is_in_system_header)
		return true;

	// Only function definitions (with bodies), not declarations.
	if (f->hasBody()) {
		Stmt* funcBody = f->getBody();

		std::unique_ptr<cfg::Cfg const> cfg = cfg::build_cfg(context, funcBody);
	}
	return true;
}

//******************************************************************************
AstConsumer::AstConsumer(ASTContext& context) : visitor(context) {}

//******************************************************************************
bool AstConsumer::HandleTopLevelDecl(DeclGroupRef dr) {
	for (DeclGroupRef::iterator it = dr.begin(); it != dr.end(); ++it) {
		// Traverse the declaration using our AST visitor.
		visitor.TraverseDecl(*it);
		(*it)->dump();
	}
	return true;
}

//******************************************************************************
std::unique_ptr<ASTConsumer> AstProcessor::CreateASTConsumer(CompilerInstance& ci, StringRef file) {
	return std::make_unique<ast_consumer>(ci.getASTContext());
}
