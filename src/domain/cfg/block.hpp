#pragma once

#include "domain/core/types.hpp"
#include "domain/core/aggregator.hpp"
#include "domain/core/core.hpp"

namespace domain::cfg {

using namespace domain::core;

class Block : public core::Entity {
public:
	using Linkables = Aggregator<Block>;

	[[nodiscard]] auto is_entry() const -> bool;
	[[nodiscard]] auto is_exit() const -> bool;
	[[nodiscard]] auto get_text() const -> std::string const*;
	[[nodiscard]] auto set_text(std::string text) -> result::Result<std::string, Failures::CANT_HAVE_ZERO_LENGTH, Failures::ALREADY_SETTED>;
	[[nodiscard]] auto get_successors() const -> Linkables const*;
	[[nodiscard]] auto add_successors(Block const* block)
		-> result::Result<Block*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto get_precedents() const -> Linkables const*;
	[[nodiscard]] auto add_precedent(Block const* block)
		-> result::Result<Block*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;

private:
	std::string _text;
	Linkables _precedents;
	Linkables _successors;
	// Kind const _kind;
};
}  // namespace domain::cfg