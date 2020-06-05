#ifndef CFG_ELEMENT_HPP
#define CFG_ELEMENT_HPP

#include <memory>
#include <string>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Analysis/CFG.h>
REENABLE_WARNINGS

namespace cfg {

//******************************************************************************
class Element {
private:
	clang::ASTContext& context;

public:
	enum Kind {
		STATEMENT,
		LOOP,
		CONDITION,
		SWITCH
	} kind;

	std::shared_ptr<clang::CFGElement> element_clang;

	Element(clang::CFGElement& _element_clang, Kind _kind, clang::ASTContext& _context);
	std::string get_text(void);
};

} // namesapce cfg

#endif // CFG_ELEMENT_HPP
