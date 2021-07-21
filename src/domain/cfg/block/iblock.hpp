#pragma once

#include "domain/core/guard.hpp"
#include "domain/core/types.hpp"
#include <map>
#include <string>

namespace cfg {

using namespace core;

template<class Concrete>
class IBlock : public core::Entity {
public:
	// enum Kind {};
	explicit IBlock(Uuid uuid) : Entity(std::move(uuid)){};

	[[nodiscard]] virtual auto is_entry() const -> bool = 0;
	[[nodiscard]] virtual auto is_exit() const -> bool = 0;
	[[nodiscard]] virtual auto get_text() const -> std::string = 0;
	// virtual Kind get_kind() const = 0;
	[[nodiscard]] virtual auto get_successors() const -> Aggregator<Concrete> const* = 0;
	[[nodiscard]] virtual auto get_precedents() const -> Aggregator<Concrete> const* = 0;
};

}  // namespace cfg
