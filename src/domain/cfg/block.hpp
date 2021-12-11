#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "domain/core/types.hpp"
#include "domain/core/aggregator.hpp"
#include "domain/core/core.hpp"

namespace domain::cfg {

using namespace domain::core;

class Block : public core::Entity {
public:
	using Linkable = Aggregator<Block>;

	[[nodiscard]] auto is_entry() const -> bool;
	[[nodiscard]] auto is_exit() const -> bool;
	[[nodiscard]] auto get_text() const -> std::string;
	[[nodiscard]] auto get_successors() const -> Linkable const*;
	[[nodiscard]] auto get_precedents() const -> Linkable const*;

private:
	std::string _text;
	Linkable _precedents;
	Linkable _successors;
	// Kind const _kind;
};
}  // namespace domain::cfg
