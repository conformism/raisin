#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../../core/types.hpp"
#include "./iblock.hpp"

namespace cfg {

class Block: public IBlock {
public:

	Block();
	auto get_uuid() const -> IBlock::Uuid override;
	// IBlock::Kind get_kind() const override;
	auto get_text() const -> std::string override;
	auto get_successors() const -> IBlock::Successors const& override;
	auto get_precedents() const -> IBlock::Precedents const& override;
private:
	std::string const _text;
	bool const _is_entry;
	bool const _is_exit;
	Uuid const _uuid;
	Precedents const *_precedents;
	Successors const *_successors;
	// Kind const _kind;
};
} // namespace cfg

