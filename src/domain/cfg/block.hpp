#pragma once

#include <memory>
#include <vector>

#include "domain/core/aggregator.hpp"
#include "domain/core/core.hpp"
#include "domain/core/types.hpp"
#include "element.hpp"

namespace domain::cfg {

class CompoundStatement;

using namespace domain::core;

class Block : public core::Entity {
public:
	using Linkables = Aggregator<Block>;

	enum class Kind {
		STATEMENT,
		LOOP,
		CONDITION,
		SWITCH,
		FUNCTION
	} kind;

	Block(Kind kind);

	[[nodiscard]] auto is_entry() const -> bool;
	[[nodiscard]] auto is_exit() const -> bool;

	[[nodiscard]] auto get_text() const -> std::string const*;
//	[[nodiscard]] auto set_text(std::string text)
	-> result::Result<std::string, Failures::CANT_HAVE_ZERO_LENGTH, Failures::ALREADY_SETTED>;
	[[nodiscard]] auto get_successors() const -> Linkables const*;
	[[nodiscard]] auto add_successor(Block const* block)
	-> result::Result<Block const*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto get_precedents() const -> Linkables const*;
	[[nodiscard]] auto add_precedent(Block const* block)
	-> result::Result<Block const*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto get_scope() const -> CompoundStatement const*;
	[[nodiscard]] auto set_scope(CompoundStatement const* compound_statement)
	-> result::Result<CompoundStatement const*, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto add_element(std::unique_ptr<Element> element)
	-> result::Result<CompoundStatement const*, Failures::ALREADY_INSIDE>;

private:
	Kind const _kind;
	CompoundStatement const* _scope;
	Linkables _precedents;
	Linkables _successors;
	std::vector<std::unique_ptr<Element>> _elements;
//	std::string _text;
};
}  // namespace domain::cfg
