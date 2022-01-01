#include "domain/core/compositor.hpp"
#include "file.hpp"

#include <filesystem>
#include <variant>

namespace domain::file {

class Directory {
public:
	using Recordable = std::variant<Directory, File>;
	using Childs = std::unordered_map<std::filesystem::path, std::unique_ptr<Recordable>>;
;

	auto get_path() -> std::filesystem::path;
	auto get_parent() -> Directory const*;
	auto is_root() -> bool;
	template<class R=Directory>
	auto insert(R inserted) -> void {
		_childrens.insert_or_assign(inserted.get_path(), inserted);
	}
private:
	std::filesystem::path const _path;
	Directory* _parent;
	Childs _childrens;
};


} // namespace domain::file
