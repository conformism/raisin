#include "domain/core/compositor.hpp"
#include "domain/core/types.hpp"
#include "file.hpp"

#include <filesystem>
#include <variant>

namespace domain::file {

class Directory : public Entity {
public:
	using Recordable = std::variant<Directory, File>;
	using Childs = core::Compositor<Recordable>;

	Directory(std::filesystem::path path);
	auto get_path() -> std::filesystem::path;
	auto get_parent() -> Directory const*;
	auto is_root() -> bool;
	template<class R=Directory>
	auto insert(R inserted) ->
	  result::Result<R, result::Failures::INVALID_UUID, result::Failures::ALREADY_INSIDE>
	{
		_childrens.insert(inserted.get_path(), inserted);
	}
private:
	std::filesystem::path const _path;
	Directory* _parent;
	Childs _childrens;
};


} // namespace domain::file
