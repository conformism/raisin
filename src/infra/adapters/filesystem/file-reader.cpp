#include "file-reader.hpp"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <system_error>
#include <vector>

namespace infra::adapters::filesystem {

using namespace domain::core;

auto FileAdapter::configure(Config config) -> void {
	_config = config;
	_config.path = std::filesystem::absolute(_config.path);
}

auto FileAdapter::read()
  -> domain::core::result::Result<
    domain::file::File,
    domain::core::result::Failures::NO_RESOURCES
  >
{
    constexpr auto success = result::success<domain::file::File, domain::core::result::Failures::NO_RESOURCES>;
    constexpr auto failure = result::failure<domain::file::File, domain::core::result::Failures::NO_RESOURCES>;

	domain::file::File file(_config.path, domain::file::Language::CPP);

	std::ifstream file_stream(_config.path.string());
	std::size_t line_number = 0;


	if (file_stream.is_open()) {
		std::string line;
		while (std::getline(file_stream, line)) {
			const auto result = file.set_line(line_number, line);
			if(result.is_failure()) {
				// pass
			}
			++line_number;
		}
    	file_stream.close();
		return success(file);
	}
	return failure();
}

auto DirectoryAdapter::configure(Config config) -> void {
	_config = config;
	_config.path = std::filesystem::absolute(_config.path);
}

auto DirectoryAdapter::explore()
  -> domain::core::result::Result<
	std::vector<domain::file::Directory::Recordable>,
	domain::core::result::Failures::NO_RESOURCES
  >
{
    constexpr auto success = result::success<
      std::vector<domain::file::Directory::Recordable>,
      domain::core::result::Failures::NO_RESOURCES
    >;
    // TODO(dauliac): Add way to give value to failure
    constexpr auto failure = result::failure<
      std::vector<domain::file::Directory::Recordable>,
      domain::core::result::Failures::NO_RESOURCES
    >;

	domain::file::File file(_config.path, domain::file::Language::CPP);

	std::vector<domain::file::Directory::Recordable> nesteds{};
	std::vector<std::filesystem::path> failed_files{};

	std::error_code error_code;

	for (auto& nested: std::filesystem::directory_iterator(_config.path, error_code)) {
		if(error_code) {
			// std::vector<std::any> errors{error_code};
			return failure();
		}

	    std::error_code exploration_code;

		if(std::filesystem::is_directory(nested, exploration_code)) {
			domain::file::Directory dir(nested);
			nesteds.push_back(dir);
		} else if (std::filesystem::is_regular_file(nested, exploration_code)) {
			domain::file::File file(nested, domain::file::Language::CPP);
			nesteds.push_back(file);
		}

		if(exploration_code) {
			failed_files.push_back(nested.path());
		}
		// TODO(dauliac) Add way to transform
		// exception into failure
	}
    return failed_files.empty() ? success(nesteds) : failure();
}

} // namespace infra::adapters::filesystem
