
#include <sstream>
#include <string>

#include <clang/Basic/LangOptions.h>
#include <clang/Analysis/CFG.h>
#include <llvm/Support/raw_ostream.h>

#include "cfg.hpp"
#include "ast_processor.hpp"

using namespace clang;

//******************************************************************************
ast_visitor::ast_visitor(ASTContext& c, Rewriter& r)
: context(c)
, rewriter(r)
{}

//******************************************************************************
bool ast_visitor::VisitStmt(Stmt* s) {
	return true;
}

//******************************************************************************
bool ast_visitor::VisitForStmt(ForStmt* f) {
/*	if (context.getSourceManager().isInSystemHeader(f->getLParenLoc())
	||  context.getSourceManager().isInSystemHeader(f->getRParenLoc()))
		return true;

	llvm::errs() << "cond : ";
	printExprAsWritten(llvm::errs(), f->getCond(), &context);
	llvm::errs() << "\n";
	llvm::errs() << "inc : ";
	printExprAsWritten(llvm::errs(), f->getInc(), &context);
	llvm::errs() << "\n";

	llvm::errs() << "parenthesis : ";
	bool Invalid = false;
	StringRef Source = Lexer::getSourceText(
		CharSourceRange::getTokenRange(SourceRange(f->getLParenLoc(), f->getRParenLoc())),
		context.getSourceManager(), context.getLangOpts(), &Invalid);
	if (!Invalid)
		llvm::errs() << Source;
	llvm::errs() << "\n";
*/
	return true;
}

//******************************************************************************
bool ast_visitor::VisitFunctionDecl(FunctionDecl* f) {
	if (context.getSourceManager().isInSystemHeader(f->getSourceRange().getBegin())
	||  context.getSourceManager().isInSystemHeader(f->getSourceRange().getEnd())
	|| (f->isTemplateInstantiation()
	&&  context.getSourceManager().isInSystemHeader(f->getPointOfInstantiation())) )
		return true;
	// Only function definitions (with bodies), not declarations.
	if (f->hasBody()) {
		Stmt *funcBody = f->getBody();
		//CFG
		CFG::BuildOptions bo;
		bo.AddScopes = true;
		bo.AddLifetime = true;
		bo.AddImplicitDtors = true;
		bo.AddEHEdges = true;
		bo.AddInitializers = true;
		bo.AddLoopExit = true;

		bo.AddEHEdges = true;
		bo.AddInitializers = true;
		bo.AddImplicitDtors = true;
		bo.AddLifetime = true;
		bo.AddLoopExit = true;
		bo.AddTemporaryDtors = true;
		bo.AddScopes = true;
		bo.AddStaticInitBranches = true;
		bo.AddCXXNewAllocator = true;
		bo.AddCXXDefaultInitExprInCtors = true;
		bo.AddCXXDefaultInitExprInAggregates = true;
		bo.AddRichCXXConstructors = true;
		bo.MarkElidedCXXConstructors = true;
		bo.AddVirtualBaseBranches = true;
		bo.OmitImplicitValueInitializers = true;

		std::unique_ptr<CFG> cfg_clang = CFG::buildCFG(f, funcBody, &context, bo);
		cfg_clang->print(llvm::errs(), LangOptions(), true);
		// Export dot files, works with clang built in debug mode only
		// cfg_clang->viewCFG(LangOptions());

		Cfg cfg(cfg_clang, context); 

	}
	return true;
}

//******************************************************************************
ast_consumer::ast_consumer(ASTContext& c, Rewriter& r)
: visitor(c, r)
{}

//******************************************************************************
bool ast_consumer::HandleTopLevelDecl(DeclGroupRef dr) {
	for (DeclGroupRef::iterator it = dr.begin(); it != dr.end(); ++it) {
		// Traverse the declaration using our AST visitor.
		visitor.TraverseDecl(*it);
		(*it)->dump();
	}
	return true;
}

//******************************************************************************
std::unique_ptr<ASTConsumer> ast_processor::CreateASTConsumer(CompilerInstance& ci, StringRef file) {
	rewriter.setSourceMgr(ci.getSourceManager(), ci.getLangOpts());
	return std::make_unique<ast_consumer>(ci.getASTContext(), rewriter);
}
