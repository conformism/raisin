#pragma once

#include <memory>
#include <vector>

#include "./icfg.hpp"

namespace cfg {

class Cfg: public ICfg {
public:
	virtual IElement* get_element() const override;
	virtual Blocks get_blocks() const override;
	virtual IBlock* get_block_by_id(Uuid uuid) const override;
	virtual Scopes get_scopes() const override;
	virtual IScope* get_scope_by_id(Uuid uuid) const override;
private:
	IElement* const _element;
	Blocks const _blocks;
	Scopes const _scopes;

	Cfg(IElement* element, ICfg::Blocks blocks, ICfg::Scopes scopes);
};

} // namespace cfg
