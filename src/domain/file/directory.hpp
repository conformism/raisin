#include "domain/core/compositor.hpp"
#include "file.hpp"

#include <filesystem>
#include <variant>

namespace domain::file {

class Directory {
public:
	using Childs = core::Compositor<std::variant<Directory, File>>;

	auto get_path() -> std::filesystem::path;
	auto get_parent(Directory dir) -> Directory const*;
	auto is_root() -> bool;
	auto insert(Directory dir) -> Directory;
	auto insert(File file) -> File;
private:
	std::filesystem::path const _path;
	Directory* _parent;
	Childs _childrens;
};


} // namespace domain::file
