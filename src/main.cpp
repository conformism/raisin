///*****************************************************************************
/// @file      main.cpp
/// @copyright GPL-3.0-or-later
/// @author    Thomas Lepoix <thomas.lepoix@protonmail.ch>
/// @author    Dauliac <dauliac@protonmail.com>
///*****************************************************************************

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
REENABLE_WARNINGS

#include "domain/factories/cpp/ast_processor.hpp"

using namespace clang::tooling;

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");

int main(int argc, const char** argv) {
	CommonOptionsParser op(argc, argv, ToolingSampleCategory);
	ClangTool tool(op.getCompilations(), op.getSourcePathList());

	// ClangTool::run accepts a FrontendActionFactory, which is then used to
	// create new objects implementing the FrontendAction interface. Here we use
	// the helper newFrontendActionFactory to create a default factory that will
	// return a new ast_processor object every time.
	// To further customize this, we could create our own factory class.
	return tool.run(newFrontendActionFactory<ast_processor>().get());
}
