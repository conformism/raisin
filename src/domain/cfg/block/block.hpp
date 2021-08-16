#pragma once

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
	friend Builder;

protected:
	Block(
		Uuid uuid,
		bool is_entry,
		bool is_exit,
		Aggregator<Block> precedent,
		Aggregator<Block> sucessors);

private:
	std::string const _text;
	bool const _is_entry;
	bool const _is_exit;
	Aggregator<Block> const _precedents;
	Aggregator<Block> const _successors;
	// Kind const _kind;
};

class Block::Builder : public IBlock<Block>::IBuilder {
public:
	auto set_uuid(Uuid uuid) -> IBuilder* override;
	auto set_text(std::string text) -> IBuilder* override;
	auto define_as_entry(bool is_entry) -> IBuilder* override;
	auto define_as_exit(bool is_exit) -> IBuilder* override;
	auto add_precedent(Block* block) -> IBuilder* override;
	auto add_successor(Block* block) -> IBuilder* override;
	auto set_precedents(Block* blocks) -> IBuilder* override;
	auto set_successors(Block* blocks) -> IBuilder* override;
	[[nodiscard]] auto build() const -> Block override;

private:
	Uuid _uuid;
	std::string _text;
	bool _is_entry;
	bool _is_exit;
	Aggregator<Block>* _precedents;
	Aggregator<Block>* _successors;
	Block* _builded;
};

}  // namespace cfg
