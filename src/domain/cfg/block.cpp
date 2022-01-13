#include "domain/core/types.hpp"
#include <string>
#include <utility>

#include "./block.hpp"

using namespace std;

namespace domain::cfg {

Block::Block(file::Code code, Kind kind)
: _code(std::move(code)), _kind(kind)
{};

auto Block::is_entry() const -> bool {
	return _precedents.empty();
}

auto Block::is_exit() const -> bool {
	return _successors.empty();
}

auto Block::get_code() const -> file::Code const& {
	return _code;
}

auto Block::set_code(file::Code code) -> void
{
	_code = std::move(code);
}

auto Block::get_successors() const -> Aggregator<Block> const* {
	return &_successors;
}

auto Block::get_precedents() const -> Aggregator<Block> const* {
	return &_precedents;
}
}  // namespace domain::cfg
