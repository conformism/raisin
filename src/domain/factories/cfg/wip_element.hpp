#pragma once

#include "domain/cfg/element.hpp"

namespace cfg {

//******************************************************************************
class WipElement : public Element {
public:
	WipElement(clang::ASTContext& _context, clang::Stmt const* _stmt);
	
	std::string get_text(void);
};

} // namesapce cfg
