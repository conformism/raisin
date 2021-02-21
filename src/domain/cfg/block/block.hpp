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
	IBlock::Uuid get_uuid() const override;
	// IBlock::Kind get_kind() const override;
	std::string get_text() const override;
	IBlock::Successors get_successors() const override;
	IBlock::Precedents get_precedents() const override;
private:
	std::string const _text;
	bool const _is_entry;
	bool const _is_exit;
	Uuid const _uuid;
	Precedents const _precedents;
	Successors const _successors;
	// Kind const _kind;
};
} // namespace cfg

