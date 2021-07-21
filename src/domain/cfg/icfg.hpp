#pragma once

#include <memory>
#include <utility>

#include "../core/guard.hpp"
#include "../core/types.hpp"

#include "./element/ielement.hpp"
#include "./scope/iscope.hpp"

namespace cfg {

using namespace core;

template<class Concrete, class ConcreteBlock, class ConcreteScope>
class ICfg : public Entity {
public:
	explicit ICfg(Uuid uuid) : Entity(std::move(uuid)){};
	// virtual ~ICfg() = default;
	// [[nodiscard]] virtual auto get_uuid(Uuid uuid) const -> Uuid = 0;
	[[nodiscard]] virtual auto get_block_by_id(Uuid uuid) const -> result::
		BasicDomainResult<std::weak_ptr<ConcreteBlock>, guard::InvalidArgumentParameter> = 0;
	[[nodiscard]] virtual auto get_scope_by_id(Uuid uuid) const -> result::
		BasicDomainResult<std::weak_ptr<ConcreteScope>, guard::InvalidArgumentParameter> = 0;
	class IBuilder {
	public:
		// virtual ~IBuilder() = default;
		virtual auto set_uuid(Uuid uuid) -> IBuilder* = 0;
		virtual auto add_block(ConcreteBlock* block) -> IBuilder* = 0;
		virtual auto add_scope(ConcreteScope* scope) -> IBuilder* = 0;
		virtual auto set_blocks(Compositor<ConcreteBlock>* blocks) -> IBuilder* = 0;
		virtual auto set_scopes(Compositor<ConcreteScope>* scopes) -> IBuilder* = 0;
		[[nodiscard]] virtual auto build() const -> ICfg* = 0;
	};

protected:
	using Self = Concrete;
	using SelfBlock = ConcreteBlock;
};

}  // namespace cfg
