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

	class IBuilder {
		public:
			virtual ~IBuilder() = default;
			virtual IBuilder* set_uuid(core::Uuid uuid) = 0;
			virtual IBuilder* add_block(IBlock block) = 0;
			virtual IBuilder* add_scope(IScope scope) = 0;
			virtual IBuilder* set_blocks(Blocks blocks) = 0;
			virtual IBuilder* set_scopes(Scopes scopes) = 0;
			virtual ICfg* build() const = 0;
	};
};

} // namespace cfg
