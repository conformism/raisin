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
	virtual IBlock* get_block_by_id(Uuid uuid) const = 0;
	virtual IScope* get_scope_by_id(Uuid uuid) const = 0;
	class Builder {
		public:

	};
};

} // namespace cfg
