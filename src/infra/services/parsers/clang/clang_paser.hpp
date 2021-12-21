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
#include "ast_processor.hpp"

namespace infra::services::parser::clang {

class ClangParser {
public:
    struct Config {
		std::filesystem::path compilation_database_dir;
    };

    ClangParser(Config config);

    auto run() -> void;

private:
    static llvm::cl::OptionCategory const option_category;
    std::string error_message;

    std::unique_ptr<::clang::tooling::CompilationDatabase> compilation_database;
    ::clang::tooling::ClangTool tool;

    domain::IRespository<domain::Program>* repository;
};

} // namespace infra::services::parser::clang
