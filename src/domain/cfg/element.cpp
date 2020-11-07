#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/Lex/Lexer.h>
REENABLE_WARNINGS

#include "domain/cfg/element.hpp"

using namespace std;
using namespace clang;

namespace cfg {

//******************************************************************************
Element::Element(ASTContext& _context, Stmt const* _stmt)
: context(_context)
, stmt(_stmt)
{}

//******************************************************************************


} // namespace cfg
