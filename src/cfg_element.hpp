#ifndef CFG_ELEMENT_HPP
#define CFG_ELEMENT_HPP

#include <memory>
#include <string>

#include <clang/Analysis/CFG.h>

//******************************************************************************
class CfgElement {
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

	CfgElement(clang::CFGElement& _element_clang, Kind _kind, clang::ASTContext& _context);
	std::string get_text(void);
};

#endif // CFG_ELEMENT_HPP
