#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../../core/types.hpp"
#include "./iblock.hpp"

namespace cfg {

using namespace core;

class Block : public IBlock<Block> {
public:
	// IBlock::Kind get_kind() const override;
	Block(
		Uuid uuid,
		bool is_entry,
		bool is_exit,
		Aggregator<Block> const& precedent,
		Aggregator<Block> const& sucessors);
	[[nodiscard]] auto is_entry() const -> bool override;
	[[nodiscard]] auto is_exit() const -> bool override;
	[[nodiscard]] auto get_text() const -> std::string override;
	[[nodiscard]] auto get_successors() const -> Aggregator<Block> const* override;
	[[nodiscard]] auto get_precedents() const -> Aggregator<Block> const* override;

private:
	std::string const _text;
	bool const _is_entry;
	bool const _is_exit;
	Aggregator<Block> const* _precedents;
	Aggregator<Block> const* _successors;
	// Kind const _kind;
};
}  // namespace cfg
