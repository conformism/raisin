#pragma once

#include "domain/core/compositor.hpp"
#include "domain/core/result.hpp"
#include <filesystem>
#include <map>

namespace domain::file {

using namespace core;

enum class Language {
	C,
	CPP,
};

class File {
public:
	using LineNumber = int;
	using Line = std::string;
	using Lines = std::map<LineNumber, Line>;

	[[nodiscard]] auto get_lang() const -> Language;
	[[nodiscard]] auto get_path() const -> std::filesystem::path;
	[[nodiscard]]
	auto get_content(
	  int start_line,
	  int last_line
	) const -> result::Result<File::Lines>;
private:
	Lines _lines;
	Language _lang;
	std::filesystem::path _path;
};
} // namespace domain::file
