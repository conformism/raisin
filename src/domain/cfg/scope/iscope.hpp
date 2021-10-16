#pragma once

#include "domain/core/aggregator.hpp"
#include <map>
#include <optional>
#include <vector>

#include "../../core/types.hpp"

namespace cfg {

using namespace core;

template<class Concrete, class ConcreteBlock>
class IScope : public Entity {
public:
	using Parent = Concrete const*;
	using Blocks = core::Aggregator<ConcreteBlock>;
	using Childs = core::Aggregator<Concrete>;

	IScope() : Entity(){};
	explicit IScope(core::Uuid uuid) : Entity(std::move(uuid)){};
	[[nodiscard]] virtual auto is_root() const -> bool = 0;
	[[nodiscard]] virtual auto has_childs() const -> bool = 0;
	[[nodiscard]] virtual auto get_blocks() const -> Blocks = 0;
	[[nodiscard]] virtual auto get_childs() const -> Childs = 0;
	[[nodiscard]] virtual auto get_parent() const -> Parent = 0;

	template<class ConcreteBuilder>
	class IBuilder : Builder<Concrete> {
	public:
		// virtual ~IBuilder() = default;
		virtual auto set_uuid(Uuid uuid)
			-> result::Result<ConcreteBuilder*, Failures::INVALID_UUID> = 0;
		virtual auto add_child(Concrete* child) -> result::
			Result<ConcreteBuilder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> = 0;
		virtual auto set_parent(Concrete* parent) -> result::
			Result<ConcreteBuilder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> = 0;
		virtual auto add_block(ConcreteBlock* block) -> result::
			Result<ConcreteBuilder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> = 0;
	};
};

}  // namespace cfg
