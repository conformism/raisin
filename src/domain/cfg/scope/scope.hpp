#pragma once

#include <memory>
#include <vector>

#include "../block/iblock.hpp"
#include "iscope.hpp"

namespace cfg {

using namespace core;

class Scope : public IScope {
private:
    // TODO: check if there is way to put
    // it into const, and if we need to
    // add setter
    mutable Parent _parent;
    const Blocks _blocks;
    const Childs _childs;

public:
    Blocks get_blocks() const override;
    Childs get_childs() const override;
    Parent get_parent() const override;
};

}  // namespace cfg
