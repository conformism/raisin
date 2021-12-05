#pragma once

#include <memory>
#include <utility>

#include "../core/guard.hpp"
#include "../core/types.hpp"

#include "./block/iblock.hpp"
#include "./element/ielement.hpp"
#include "./scope/iscope.hpp"

namespace domain::cfg {

using namespace domain::core;

template<class Concrete, class ConcreteBlock, class ConcreteScope>
class ICfg : public Entity {
public:
	ICfg() : Entity(){};
	explicit ICfg(Uuid uuid) : Entity(std::move(uuid)){};
	virtual ~ICfg() = default;

	[[nodiscard]] virtual auto get_block_by_id(Uuid uuid) const
		-> result::Result<ConcreteBlock*, Failures::INVALID_UUID, Failures::NOT_INSIDE> = 0;
	[[nodiscard]] virtual auto get_scope_by_id(Uuid uuid) const
		-> result::Result<ConcreteScope*, Failures::INVALID_UUID, Failures::NOT_INSIDE> = 0;

	template<class ConcreteBuilder>
	class IBuilder {
	public:
		[[nodiscard]] virtual auto set_uuid(Uuid uuid)
			-> result::Result<ConcreteBuilder*, Failures::INVALID_UUID> = 0;
		[[nodiscard]] virtual auto add_block(ConcreteBlock block) -> result::
			Result<ConcreteBuilder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> = 0;
		[[nodiscard]] virtual auto add_scope(ConcreteScope scope) -> result::
			Result<ConcreteBuilder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> = 0;
		[[nodiscard]] virtual auto build() -> Concrete = 0;
	};
};

}  // namespace domain::cfg
