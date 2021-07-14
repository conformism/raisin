#pragma once

#include <map>
#include <vector>

#include "../../core/types.hpp"

namespace cfg {

class IBlock;

class IScope {
public:
    using Uuid = core::Uuid;
    using Parent = IScope*;
    using Blocks = core::Aggregator<IBlock>;
    using Childs = core::Aggregator<IScope>;

    virtual ~IScope() = default;
    virtual auto get_uuid() const -> Uuid = 0;
    virtual auto get_blocks() const -> Blocks = 0;
    virtual auto get_childs() const -> Childs = 0;
    virtual auto get_parent() const -> Parent = 0;
};

}  // namespace cfg
