#include <vector>

#include <clang/AST/Stmt.h>

class Element {
	public:
		std::shared_ptr<clang::Stmt> parent;
		std::shared_ptr<std::shared_ptr<clang::Stmt>> childrens;
		std::shared_ptr<clang::Stmt> statment;
};
