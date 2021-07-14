#include <string>

#include "./block.hpp"

using namespace std;

namespace cfg {

auto Block::get_text() const -> std::string {
    return _text;
}

// IBlock::Kind Block::get_kind() const {
//     return _kind;
// }

auto Block::get_successors() const -> IBlock::Successors const& {
    return *_successors;
}

auto Block::get_precedents() const -> IBlock::Precedents const& {
    return *_precedents;
}

}  // namespace cfg
