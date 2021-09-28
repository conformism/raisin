#pragma once

#include <memory>
#include <vector>

#include "block/block.hpp"
#include "icfg.hpp"
#include "scope/scope.hpp"

namespace cfg {

class Cfg : public ICfg<Cfg, Block, Scope> {
public:
	[[nodiscard]] auto get_block_by_id(Uuid uuid) const -> result::Result<
		result::Success<Block*>,
		result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> override;
	[[nodiscard]] auto get_scope_by_id(Uuid uuid) const -> result::Result<
		result::Success<Scope*>,
		result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> override;
	class Builder;
	friend IBuilder<Builder>;

private:
	Cfg(  // IElement* element,
		Aggregator<Block> blocks,
		Aggregator<Scope> scopes);
	Cfg(Uuid uuid,
	    // IElement* element,
	    Aggregator<Block> blocks,
	    Aggregator<Scope> scopes);

	const Uuid uuid;
	// TODO(dauliac): not used yet
	// IElement* const _element;
	Aggregator<Block> const _blocks;
	Aggregator<Scope> const _scopes;
};

class Cfg::Builder : public ICfg::IBuilder<Builder> {
public:
	auto set_uuid(Uuid uuid) -> result::Result<
		result::Success<ConcreteBuilder&>,
		result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> auto add_block(Block* block)
		-> result::Result<
			result::Success<Builder&>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>> override;
	auto add_scope(Scope* scope) -> result::Result<
		result::Success<Builder&>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>> override;
	[[nodiscard]] auto build() -> Cfg override;

private:
	Uuid _uuid;
	Aggregator<Block> _blocks;
	Aggregator<Scope> _scopes;
};

}  // namespace cfg
