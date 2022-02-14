#include "directory.hpp"

namespace domain::file {

Directory::Directory(std::filesystem::path path)
: _path(std::move(path))
{}

auto Directory::get_path() -> std::filesystem::path {
	return _path;
}
auto Directory::get_parent() -> Directory const* {
	return _parent;
};
auto Directory::is_root() -> bool {
	return _parent == nullptr;
}
} // namespace domain::file
