#pragma once

#include <filesystem>
#include <vector>

#include "domain/file/file.hpp"
#include "domain/core/types.hpp"
#include "domain/file/directory.hpp"
#include "domain/core/types.hpp"

namespace infra::adapters::filesystem {

class FileAdapter {
public:

	struct Config {
		std::filesystem::path path;
	};

    auto configure(Config config) -> void;
    auto read() -> domain::core::result::Result<
	  domain::file::File,
	  domain::core::result::Failures::NO_RESOURCES
	>;

private:
	Config _config;

};

class DirectoryAdapter {
public:

	struct Config {
		std::filesystem::path path;
	};

    auto configure(Config config) -> void;
    auto explore() -> domain::core::result::Result<
	  std::vector<domain::file::Directory::Recordable>,
	  domain::core::result::Failures::NO_RESOURCES
	>;

private:
	Config _config;

};

} // namespace infra::adapters::filesystem
