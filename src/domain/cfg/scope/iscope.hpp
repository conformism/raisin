#pragma once

#include <vector>
#include <map>

#include "../../core/types.hpp"

using namespace core;

namespace cfg {

class IBlock;

class IScope {
public:
	using Uuid = core::Uuid;
	using Parent = IScope*;
	using Blocks = core::Aggregator<IBlock>;
	using Childs = core::Aggregator<IScope>;

	virtual ~IScope() = default;
	virtual Uuid get_uuid() const = 0;
	virtual Blocks get_blocks() const = 0;
	virtual Childs get_childs() const = 0;
	virtual Parent get_parent() const = 0;
};

} // namespace cfg
