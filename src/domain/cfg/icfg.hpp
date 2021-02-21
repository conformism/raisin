#pragma once

#include "../core/types.hpp"

#include "./block/iblock.hpp"
#include "./scope/iscope.hpp"
#include "./element/ielement.hpp"

namespace cfg {

class ICfg {
public:
	using Uuid = core::Uuid;
	using Blocks = core::Compositor<IBlock>;
	using Scopes = core::Compositor<IScope>;

	virtual ~ICfg() = default;
	virtual IElement* get_element() const  = 0;
	virtual Blocks get_blocks() const = 0;
	virtual IBlock* get_block_by_id(Uuid uuid) const = 0;
	virtual Scopes get_scopes() const = 0;
	virtual IScope* get_scope_by_id(Uuid uuid) const = 0;
};

} // namespace cfg
