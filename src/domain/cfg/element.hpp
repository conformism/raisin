#pragma once

#include <memory>
#include <string>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

namespace cfg {

//******************************************************************************
class Element {
protected:
	clang::ASTContext& context;
	clang::Stmt const* stmt;

public:
	Element(clang::ASTContext& _context, clang::Stmt const* _stmt);
};

} // namesapce cfg
