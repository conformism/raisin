#pragma once

#include "domain/core/core.hpp"
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

	class IBuilder : Builder<Concrete> {
	public:
		virtual auto set_uuid(Uuid uuid) -> IBuilder* = 0;
		virtual auto set_text(std::string text) -> IBuilder* = 0;
		virtual auto define_as_entry(bool is_entry) -> IBuilder* = 0;
		virtual auto define_as_exit(bool is_exit) -> IBuilder* = 0;
		virtual auto add_precedent(Concrete* block) -> IBuilder* = 0;
		virtual auto add_successor(Concrete* block) -> IBuilder* = 0;
		virtual auto set_precedents(Concrete* blocks) -> IBuilder* = 0;
		virtual auto set_successors(Concrete* blocks) -> IBuilder* = 0;
	};
};

}  // namespace cfg
