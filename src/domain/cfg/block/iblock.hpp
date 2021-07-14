#pragma once

#include "../../core/types.hpp"
#include <map>
#include <string>

namespace cfg {

using namespace core;

class IBlock : public core::Entity {
public:
    // enum Kind {};
    using Precedents = Aggregator<IBlock>;
    using Successors = Aggregator<IBlock>;

    [[nodiscard]] virtual auto is_entry() const -> bool = 0;
    [[nodiscard]] virtual auto is_exit() const -> bool = 0;
    [[nodiscard]] virtual auto get_text() const -> std::string = 0;
    // virtual Kind get_kind() const = 0;
    [[nodiscard]] virtual auto get_successors() const -> Successors const& = 0;
    [[nodiscard]] virtual auto get_precedents() const -> Precedents const& = 0;
};

}  // namespace cfg
