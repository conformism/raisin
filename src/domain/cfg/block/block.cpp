#include <string>

#include "./block.hpp"

using namespace std;

namespace cfg {

Block::Block(
	Uuid uuid,
	bool is_entry,
	bool is_exit,
	Aggregator<Block> const& precedent,
	Aggregator<Block> const& sucessors)
	: IBlock<Block>(std::move(uuid)),
	  _is_entry(is_entry),
	  _is_exit(is_exit),
	  _precedents(&precedent),
	  _successors(&sucessors) {}

auto Block::is_entry() const -> bool {
	return _is_entry;
}

auto Block::is_exit() const -> bool {
	return _is_exit;
}

auto Block::get_text() const -> std::string {
	return _text;
}

auto Block::get_successors() const -> Aggregator<Block> const* {
	return _successors;
}

auto Block::get_precedents() const -> Aggregator<Block> const* {
	return _precedents;
}
}  // namespace cfg
