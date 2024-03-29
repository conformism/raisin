#include "file.hpp"

#include <utility>

namespace domain::file {

File::File(std::filesystem::path path, Language language)
: _path(std::move(path)), _language(language), _includes()
{}

auto File::get_language() const -> Language {
	return _language;
}

auto File::get_path() const -> std::filesystem::path {
	return _path;
}

auto File::include(File* file) -> result::Result<File*, Failures::ALREADY_INSIDE> {
	auto const result = _includes.insert(file->get_uuid(), file);
	return result.set_failures<Failures::ALREADY_INSIDE>().value();
}

auto File::get_include(Uuid const& uuid) -> result::Result<File*, Failures::NOT_INSIDE> {
	auto const result = _includes.at(uuid);
	return result.set_failures<Failures::NOT_INSIDE>().value();
}

auto File::get_content(int start_line, int last_line)
  const -> result::Result<File::Lines> {
	File::Lines subset{};
	auto start_line_range = _lines.lower_bound(start_line);
	auto end_line_range = _lines.upper_bound(last_line);
	subset.insert(start_line_range, end_line_range);

	return result::success<File::Lines>(std::move(subset));
}

} // namespace domain::file
