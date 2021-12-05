#include <sstream>
#include <string>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
// #include <clang/Analysis/CFG.h>
#include <clang/Basic/LangOptions.h>
#include <llvm/Support/raw_ostream.h>
REENABLE_WARNINGS

#include "ast_processor.hpp"
#include "cfg_factory.hpp"

namespace infra::services::parser::clang {
using namespace ::clang;
// using namespace cfg;

//******************************************************************************
AstVisitor::AstVisitor(ASTContext& c) : context(c) {}

//******************************************************************************
bool AstVisitor::VisitFunctionDecl(FunctionDecl* f) {
	bool const is_in_system_header =
		context.getSourceManager().isInSystemHeader(f->getSourceRange().getBegin())
		|| context.getSourceManager().isInSystemHeader(f->getSourceRange().getEnd())
		|| (f->isTemplateInstantiation()
	        && context.getSourceManager().isInSystemHeader(f->getPointOfInstantiation()));
	if (is_in_system_header) {
		return true;
	}

	// Only function definitions (with bodies), not declarations.
	if (f->hasBody()) {
		Stmt* funcBody = f->getBody();

		std::unique_ptr<domain::cfg::Cfg const> cfg = build_cfg(context, funcBody);
	}
	return true;
}

//******************************************************************************
AstConsumer::AstConsumer(ASTContext& context) : visitor(context) {}

//******************************************************************************
bool AstConsumer::HandleTopLevelDecl(DeclGroupRef dr) {
	for (auto& it : dr) {
		// Traverse the declaration using our AST visitor.
		visitor.TraverseDecl(it);
		it->dump();
	}
	return true;
}

//******************************************************************************
std::unique_ptr<ASTConsumer> AstProcessor::CreateASTConsumer(CompilerInstance& ci, StringRef file) {
	return std::make_unique<AstConsumer>(ci.getASTContext());
}

}  // namespace infra::services::parser::clang
