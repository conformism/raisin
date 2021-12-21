#include "clang_paser.hpp"

using namespace std;

namespace infra::services::parser::clang {

llvm::cl::OptionCategory const ClangParser::option_category("Tooling Sample");

ClangParser::ClangParser(ClangParser::Config config)
: error_message()
, compilation_database(
	::clang::tooling::CompilationDatabase::autoDetectFromDirectory(
	llvm::StringRef(config.compilation_database_dir.string()), error_message))
, tool(*compilation_database.get(), config.compilation_database_dir.string())
{}

auto ClangParser::run() -> void {
    tool.run(::clang::tooling::newFrontendActionFactory<AstProcessor>().get());
}

} // namespace infra::services::parser::clang
