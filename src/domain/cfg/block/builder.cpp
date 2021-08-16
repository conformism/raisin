#include "./block.hpp"
#include <memory>

namespace cfg {

auto Block::Builder::set_uuid(core::Uuid uuid) -> IBlock::IBuilder* {
	uuid = uuid;
	return this;
}

auto Block::Builder::set_text(std::string text) -> IBlock::IBuilder* {
	// todo(dauliac) maybe add a guard to check if string is null
	_text = text;
	return this;
}

auto Block::Builder::define_as_entry(bool is_entry) -> IBlock::IBuilder* {
	_is_entry = is_entry;
	return this;
}

auto Block::Builder::define_as_exit(bool is_exit) -> IBlock::IBuilder* {
	_is_exit = is_exit;
	return this;
}

auto Block::Builder::add_precedent(Block* block) -> IBlock::IBuilder* {
	_precedents->insert(std::pair<Uuid, Block*>(block->get_uuid(), block));
	return this;
}

auto Block::Builder::build() const -> Block {
	return Block(_uuid, *_blocks, *_scopes);
}
}  // namespace cfg
