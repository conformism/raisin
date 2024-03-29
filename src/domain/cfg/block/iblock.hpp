#pragma once

#include "domain/core/core.hpp"
#include <map>
#include <string>

namespace domain::cfg {

using namespace domain::core;

template<class Concrete>
class IBlock : public domain::core::Entity {
public:
	// enum Kind {};
	explicit IBlock() : Entity(){};
	explicit IBlock(Uuid uuid) : Entity(std::move(uuid)){};

	[[nodiscard]] virtual auto is_entry() const -> bool = 0;
	[[nodiscard]] virtual auto is_exit() const -> bool = 0;
	[[nodiscard]] virtual auto get_text() const -> std::string = 0;
	// virtual Kind get_kind() const = 0;
	[[nodiscard]] virtual auto get_successors() const -> Aggregator<Concrete> const* = 0;
	[[nodiscard]] virtual auto get_precedents() const -> Aggregator<Concrete> const* = 0;

	template<class ConcreteBlock>
	class IBuilder : Builder<Concrete> {
	public:
		virtual auto set_uuid(Uuid uuid)
			-> result::Result<ConcreteBlock*, Failures::INVALID_UUID> = 0;
		virtual auto set_text(std::string text) -> ConcreteBlock* = 0;
		virtual auto add_precedent(Concrete* precedent)
			-> result::Result<ConcreteBlock*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> = 0;
		virtual auto add_successor(Concrete* successor)
			-> result::Result<ConcreteBlock*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> = 0;
	};
};

}  // namespace domain::cfg
