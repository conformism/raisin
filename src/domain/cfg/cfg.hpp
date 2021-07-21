#pragma once

#include <memory>
#include <vector>

#include "./block/block.hpp"
#include "./icfg.hpp"
#include "./scope/scope.hpp"

namespace cfg {

class Cfg : public ICfg<Cfg, Block, Scope> {
public:
	Cfg(Uuid uuid,
	    IElement* element,
	    const Aggregator<Block>& blocks,
	    const Aggregator<Scope>& scopes);
	[[nodiscard]] auto get_block_by_id(Uuid uuid) const -> result::
		BasicDomainResult<std::weak_ptr<Block>, guard::InvalidArgumentParameter> override;
	[[nodiscard]] auto get_scope_by_id(Uuid uuid) const -> result::
		BasicDomainResult<std::weak_ptr<Scope>, guard::InvalidArgumentParameter> override;
	class Builder;
	// TODO(dauliac) consider using struct to store object properties
	// and easily pass it from dump/builder/factory.
private:
	const Uuid uuid;
	// TODO(dauliac): not used yet
	IElement* const _element;
	Aggregator<Block> const* _blocks;
	Aggregator<Scope> const* _scopes;
};

class Cfg::Builder : public ICfg::IBuilder {
public:
	auto set_uuid(Uuid uuid) -> ICfg::IBuilder* override;
	auto add_block(Block* block) -> ICfg::IBuilder* override;
	auto add_scope(Scope* scope) -> ICfg::IBuilder* override;
	auto set_blocks(Compositor<Block>* blocks) -> ICfg::IBuilder* override;
	auto set_scopes(Compositor<Scope>* scopes) -> ICfg::IBuilder* override;
	[[nodiscard]] auto build() const -> ICfg* override;

private:
	Uuid uuid;
	Aggregator<Block>* _blocks;
	Aggregator<Scope>* _scopes;
	ICfg* _builded;
};

}  // namespace cfg
