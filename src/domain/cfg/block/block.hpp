#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "./iblock.hpp"
#include "domain/core/aggregator.hpp"
#include "domain/core/core.hpp"

namespace cfg {

using namespace core;

class Block : public IBlock<Block> {
public:
	[[nodiscard]] auto is_entry() const -> bool override;
	[[nodiscard]] auto is_exit() const -> bool override;
	[[nodiscard]] auto get_text() const -> std::string override;
	[[nodiscard]] auto get_successors() const -> Aggregator<Block> const* override;
	[[nodiscard]] auto get_precedents() const -> Aggregator<Block> const* override;
	class Builder;
	friend IBuilder<Builder>;

private:
	Block(Aggregator<Block> precedents, Aggregator<Block> successors);
	Block(core::Uuid uuid, Aggregator<Block> precedents, Aggregator<Block> successors);

	std::string const _text;
	Aggregator<Block> const _precedents;
	Aggregator<Block> const _successors;
	// Kind const _kind;
};

class Block::Builder : public IBlock::IBuilder<Block::Builder> {
public:
	auto set_uuid(Uuid uuid) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<Failures::INVALID_UUID>> override;
	auto set_text(std::string text) -> Builder& override;
	auto add_precedent(Block* precedent) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<
			Failures::NO_RESOURCES,
			Failures::ALREADY_INSIDE>> override;
	auto add_successor(Block* successor) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<
			Failures::NO_RESOURCES,
			Failures::ALREADY_INSIDE>> override;
	[[nodiscard]] auto build() -> Block override;

private:
	Uuid _uuid;
	std::string _text;
	Aggregator<Block> _precedents;
	Aggregator<Block> _successors;
};

}  // namespace cfg
