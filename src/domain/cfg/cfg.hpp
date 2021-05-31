#pragma once

#include <memory>
#include <vector>

#include "./icfg.hpp"

namespace cfg {

class Cfg: public ICfg {
public:
	Cfg(IElement* element, ICfg::Blocks blocks, ICfg::Scopes scopes);
	~Cfg();
	IBlock* get_block_by_id(Uuid uuid) const override;
	IScope* get_scope_by_id(Uuid uuid) const override;
	class Builder;
private:
	// TODO: not used yet
	IElement* const _element;
	Blocks const _blocks;
	Scopes const _scopes;
};

class Cfg::Builder: public ICfg::IBuilder {
	public:
		ICfg::IBuilder* set_uuid(core::Uuid uuid) override;
		ICfg::IBuilder* add_block(IBlock block) override;
		ICfg::IBuilder* add_scope(IScope scope) override;
		ICfg::IBuilder* set_blocks(Blocks blocks) override;
		ICfg::IBuilder* set_scopes(Scopes scopes) override;
		ICfg* build() const override;
	private:
		core::Uuid uuid;
		Blocks _blocks;
		Scopes _scopes;
		Cfg _builded;
	};

} // namespace cfg
