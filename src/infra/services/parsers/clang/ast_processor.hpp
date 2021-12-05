#pragma once

#include <memory>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
REENABLE_WARNINGS

namespace infra::services::parser::clang {
// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods.
//******************************************************************************
class AstVisitor : public ::clang::RecursiveASTVisitor<AstVisitor> {
private:
	::clang::ASTContext& context;

public:
	explicit AstVisitor(::clang::ASTContext& c);

	//	bool VisitForStmt(clang::ForStmt* f);
	bool VisitFunctionDecl(::clang::FunctionDecl* f);
};

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
//******************************************************************************
class AstConsumer : public ::clang::ASTConsumer {
private:
	AstVisitor visitor;

public:
	explicit AstConsumer(::clang::ASTContext& context);

	// Override the method that gets called for each parsed top-level
	// declaration.
	bool HandleTopLevelDecl(::clang::DeclGroupRef dr) override;
};

// For each source file provided to the tool, a new FrontendAction is created.
//******************************************************************************
class AstProcessor : public ::clang::ASTFrontendAction {
public:
	AstProcessor() = default;

	std::unique_ptr<::clang::ASTConsumer> CreateASTConsumer(
		::clang::CompilerInstance& ci,
		::clang::StringRef file) override;
};

}  // namespace infra::services::parser::clang
