#pragma once

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

#include "domain/cfg/element.hpp"

namespace cfg {

//******************************************************************************
class WipElement : public Element {
private:
	std::string get_str(clang::ASTContext const& context, clang::Stmt const* stmt) const;

public:
	WipElement(clang::ASTContext const& context, clang::Stmt const* stmt);
};

} // namespace cfg
