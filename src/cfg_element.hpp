#ifndef CFG_ELEMENT_HPP
#define CFG_ELEMENT_HPP

#include <memory>
#include <string>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/AST.h>
REENABLE_WARNINGS

namespace cfg {

//******************************************************************************
class Element {
private:
	clang::ASTContext& context;
	clang::Stmt const* stmt;

public:

	Element(clang::ASTContext& _context, clang::Stmt const* _stmt);
	std::string get_text(void);
};

} // namesapce cfg

#endif // CFG_ELEMENT_HPP
