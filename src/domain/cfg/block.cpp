#include "domain/core/types.hpp"
#include <string>
#include <utility>

#include "./block.hpp"

using namespace std;

namespace domain::cfg {

auto Block::is_entry() const -> bool {
	return _precedents.empty();
}

auto Block::is_exit() const -> bool {
	return _successors.empty();
}

auto Block::get_text() const -> std::string {
	return _text;
}

auto Block::get_successors() const -> Aggregator<Block> const* {
	return &_successors;
}

auto Block::get_precedents() const -> Aggregator<Block> const* {
	return &_precedents;
}
}  // namespace domain::cfg
