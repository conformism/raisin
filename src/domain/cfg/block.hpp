#pragma once

#include "domain/core/types.hpp"
#include "domain/core/aggregator.hpp"
#include "domain/core/core.hpp"
#include "domain/file/code.hpp"

namespace domain::cfg {

using namespace domain::core;

enum class Kind {
	IF,
	ELSE,
	FOR,
};

class Block : public core::Entity {
public:
	using Linkables = Aggregator<Block>;

	Block(file::Code code, Kind kind);
	[[nodiscard]] auto is_entry() const -> bool;
	[[nodiscard]] auto is_exit() const -> bool;
	[[nodiscard]] auto get_code() const -> file::Code const&;
	auto set_code(file::Code code) -> void;
	[[nodiscard]] auto get_successors() const -> Linkables const*;
	[[nodiscard]] auto add_successors(Block const* block)
		-> result::Result<Block*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto get_precedents() const -> Linkables const*;
	[[nodiscard]] auto add_precedent(Block const* block)
		-> result::Result<Block*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;

private:
	Kind _kind;
	file::Code _code;
	Linkables _precedents;
	Linkables _successors;
};
}  // namespace domain::cfg
