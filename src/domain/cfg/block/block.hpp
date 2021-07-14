#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../../core/types.hpp"
#include "./iblock.hpp"

namespace cfg {

using namespace core;

class Block : public IBlock {
public:
    Block();
    [[nodiscard]] auto get_uuid() const -> Uuid override;
    // IBlock::Kind get_kind() const override;
    [[nodiscard]] auto get_text() const -> std::string override;
    [[nodiscard]] auto get_successors() const -> IBlock::Successors const& override;
    [[nodiscard]] auto get_precedents() const -> IBlock::Precedents const& override;

private:
    std::string const _text;
    bool const _is_entry;
    bool const _is_exit;
    Uuid const _uuid;
    Precedents const* _precedents;
    Successors const* _successors;
    // Kind const _kind;
};
}  // namespace cfg
