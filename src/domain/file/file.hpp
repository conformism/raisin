#pragma once

#include "domain/core/aggregator.hpp"
#include "domain/core/compositor.hpp"
#include "domain/core/result.hpp"
#include "domain/core/types.hpp"
#include <cstddef>
#include <filesystem>
#include <map>

namespace domain::file {

using namespace core;

enum class Language {
	C,
	CPP,
};

class File : public Entity {
public:
	using LineNumber = std::size_t;
	using CharNumber = std::size_t;
	using Line = std::string;
	using Lines = std::map<LineNumber, Line>;
	using Includes = core::Aggregator<File>;
	File(std::filesystem::path path, Language language);

	[[nodiscard]] auto get_language() const -> Language;
	[[nodiscard]] auto get_path() const -> std::filesystem::path;

	[[nodiscard]]
	auto get_content(
	  CharNumber start_line,
	  CharNumber last_line
	) const -> result::Result<File::Lines>;

	[[nodiscard]]
	auto set_line(
	  LineNumber line_number,
	  std::string line
	) -> const result::Result<const File*, result::Failures::ALREADY_INSIDE>;

	auto include(
	  File* file
	) -> result::Result<File*, result::Failures::ALREADY_INSIDE>;
	auto get_include(Uuid const& uuid)
	  -> result::Result<File*, result::Failures::NOT_INSIDE>;


private:
	std::filesystem::path _path;
	Language const _language;
	Includes _includes;
	Lines _lines;
};

} // namespace domain::file
