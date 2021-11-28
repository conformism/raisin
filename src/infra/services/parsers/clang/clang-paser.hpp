#pragma once

#include "disable_warnings.hpp"
#include <initializer_list>
#include <string>
DISABLE_WARNINGS
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>
REENABLE_WARNINGS

#include "domain/cfg/cfg.hpp"
#include "domain/iprogram.hpp"
#include "domain/irepository.hpp"
#include "iclang-parser.hpp"

namespace infra::services::parser::clang {

template<class Cfg>
class ClangParser : IClangParser<Cfg> {
public:
	ClangParser(std::initializer_list<std::string> args) : option_category("Tooling Sample");
	{
		option_parser(argc, argv, option_category);
		tool(option_parser.getCompilations(), option_parser.getSourcePathList())
	}
	auto run() -> void {
		tool.run(newFrontendActionFactory<AstProcessor>().get());
	};

private:
	static llvm::cl::OptionCategory const option_category;

	// TODO(dauliac x thomas) Add util to convert args to argc + argv
	clang::tooling::CommonOptionsParser option_parser;
	ClangTool tool;

	domain::IRespository<domain::IProgram<domain::cfg::Cfg>>* repository;
};

}  // namespace infra::services::parser::clang
