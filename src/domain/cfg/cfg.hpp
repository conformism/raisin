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
private:
	IElement* const _element;
	Blocks const _blocks;
	Scopes const _scopes;
};

} // namespace cfg
