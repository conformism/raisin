#include <vector>

#include "disable_warnings.hpp"
DISABLE_WARNINGS
#include <clang/AST/Stmt.h>
REENABLE_WARNINGS

class Element {
	public:
		std::shared_ptr<clang::Stmt> parent;
		std::shared_ptr<std::shared_ptr<clang::Stmt>> childrens;
		std::shared_ptr<clang::Stmt> statment;
};
