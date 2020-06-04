#ifndef AST_PROCESSOR_HPP
#define AST_PROCESSOR_HPP

#include <memory>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Rewrite/Core/Rewriter.h>
REENABLE_WARNINGS

// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods.
//******************************************************************************
class ast_visitor : public clang::RecursiveASTVisitor<ast_visitor> {
private:
	clang::ASTContext& context;

public:
	ast_visitor(clang::ASTContext& c);

	bool VisitStmt(clang::Stmt* s);
	bool VisitForStmt(clang::ForStmt* f);
	bool VisitFunctionDecl(clang::FunctionDecl* f);
};

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
//******************************************************************************
class ast_consumer : public clang::ASTConsumer {
private:
	ast_visitor visitor;

public:
	ast_consumer(clang::ASTContext& c);

	// Override the method that gets called for each parsed top-level
	// declaration.
	bool HandleTopLevelDecl(clang::DeclGroupRef dr) override;
};

// For each source file provided to the tool, a new FrontendAction is created.
//******************************************************************************
class ast_processor : public clang::ASTFrontendAction {
public:
	ast_processor() = default;

	std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& ci, clang::StringRef file) override;
};

#endif // AST_PROCESSOR_HPP
