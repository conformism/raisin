#pragma once

#include <memory>
#include <utility>

#include "../core/guard.hpp"
#include "../core/types.hpp"

#include "./block/iblock.hpp"
#include "./element/ielement.hpp"
#include "./scope/iscope.hpp"

namespace cfg {

using namespace core;

using Result = result::
	Result<result::Success<std::any>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>>;

template<class Concrete, class ConcreteBlock, class ConcreteScope>
class ICfg : public Entity {
public:
	ICfg() : Entity(){};
	explicit ICfg(Uuid uuid) : Entity(std::move(uuid)){};
	[[nodiscard]] virtual auto get_block_by_id(Uuid uuid) const -> result::Result<
		result::Success<ConcreteBlock*>,
		result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> = 0;
	[[nodiscard]] virtual auto get_scope_by_id(Uuid uuid) const -> result::Result<
		result::Success<ConcreteScope*>,
		result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> = 0;

	template<class ConcreteBuilder>
	class IBuilder {
	public:
		[[nodiscard]] virtual auto set_uuid(Uuid uuid) -> result::Result<
			result::Success<ConcreteBuilder&>,
			result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> = 0;
		[[nodiscard]] virtual auto add_block(ConcreteBlock* block) -> result::Result<
			result::Success<ConcreteBuilder&>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>> = 0;
		[[nodiscard]] virtual auto add_scope(ConcreteScope* scope) -> result::Result<
			result::Success<ConcreteBuilder&>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>> = 0;
		[[nodiscard]] virtual auto build() -> Concrete = 0;
	};
};

}  // namespace cfg
