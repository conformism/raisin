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
	[[nodiscard]] auto is_entry() const -> bool override;
	[[nodiscard]] auto is_exit() const -> bool override;
	[[nodiscard]] auto get_text() const -> std::string override;
	[[nodiscard]] auto get_successors() const -> Aggregator<Block> const* override;
	[[nodiscard]] auto get_precedents() const -> Aggregator<Block> const* override;
	class Builder;
	friend IBuilder<Builder>;

private:
	Block(
		/*bool is_entry, bool is_exit, */ Aggregator<Block> precedents,
		Aggregator<Block> successors);
	Block(
		core::Uuid uuid,
		// bool is_entry,
	    // bool is_exit,
		Aggregator<Block> precedents,
		Aggregator<Block> successors);

	std::string const _text;
	bool const _is_entry;
	bool const _is_exit;
	Aggregator<Block> const _precedents;
	Aggregator<Block> const _successors;
	// Kind const _kind;
};

class Block::Builder : public IBlock::IBuilder<Block::Builder> {
public:
	auto set_uuid(Uuid uuid) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> override;
	auto set_text(std::string text) -> Builder& override;
	auto define_as_entry(bool is_entry) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>> override;
	auto define_as_exit(bool is_exit) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>> override;
	auto add_precedent(Block* precedent) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>> override;
	auto add_successor(Block* successor) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>> override;
	auto set_precedents(Aggregator<Block>* precedents) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> override;
	auto set_successors(Aggregator<Block>* successors) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> override;
	[[nodiscard]] auto build() -> Block override;

private:
	Uuid _uuid;
	std::string _text;
	bool _is_entry;
	bool _is_exit;
	Aggregator<Block>* _precedents;
	Aggregator<Block>* _successors;
	IBlock* _builded;
};

}  // namespace cfg
