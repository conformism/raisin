#pragma once

#include "disable_warnings.hpp"
#include <initializer_list>
#include <string>
#include <filesystem>

DISABLE_WARNINGS
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/ADT/StringRef.h>
REENABLE_WARNINGS

#include "domain/cfg/cfg.hpp"
#include "domain/irepository.hpp"
#include "domain/program.hpp"
#include "iclang-parser.hpp"
#include "ast_processor.hpp"

namespace infra::services::parser::clang {

template<class Cfg>
class ClangParser : IClangParser<Cfg> {
public:
    struct Config {
        std::filesystem::path compilation_database_dir;
    };

    ClangParser(Config config)
	: error_message()
	, compilation_database(
		::clang::tooling::CompilationDatabase::autoDetectFromDirectory(
		llvm::StringRef(config.compilation_database_dir.string), error_message))
	, tool(*compilation_database.get(), config.compilation_database_dir.string)
    {

    }

    auto run() -> void {
        tool.run(::clang::tooling::newFrontendActionFactory<AstProcessor>().get());
    }

private:
    static llvm::cl::OptionCategory const option_category;
    std::string error_message;

    // TODO(dauliac x thomas) Add util to convert args to argc + argv
    std::unique_ptr<::clang::tooling::CompilationDatabase> compilation_database;
    ::clang::tooling::ClangTool tool;

    domain::IRespository<domain::Program>* repository;
};

template<class Cfg>
llvm::cl::OptionCategory const ClangParser<Cfg>::option_category("Tooling Sample");

} // namespace infra::services::parser::clang
