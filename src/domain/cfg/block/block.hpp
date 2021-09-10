#pragma once

#include "domain/core/aggregator.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "./iblock.hpp"
#include "domain/core/core.hpp"

namespace cfg {

using namespace core;

class Block : public IBlock<Block> {
public:
	Block(bool is_entry, bool is_exit, Aggregator<Block> precedents, Aggregator<Block> successors);

	Block(
		core::Uuid uuid,
		bool is_entry,
		bool is_exit,
		Aggregator<Block> precedents,
		Aggregator<Block> successors);

	[[nodiscard]] auto is_entry() const -> bool override;
	[[nodiscard]] auto is_exit() const -> bool override;
	[[nodiscard]] auto get_text() const -> std::string override;
	[[nodiscard]] auto get_successors() const -> Aggregator<Block> const* override;
	[[nodiscard]] auto get_precedents() const -> Aggregator<Block> const* override;
	class Builder;
	friend Builder;

private:
	std::string const _text;
	bool const _is_entry;
	bool const _is_exit;
	Aggregator<Block> const _precedents;
	Aggregator<Block> const _successors;
	// Kind const _kind;
};
}  // namespace cfg
