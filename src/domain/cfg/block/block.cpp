#include <string>

#include "./block.hpp"

using namespace std;

namespace cfg {

IBlock::Uuid Block::get_uuid() const {
	return _uuid;
}

std::string Block::get_text() const {
	return _text;
}

// IBlock::Kind Block::get_kind() const {
//     return _kind;
// }

IBlock::Successors Block::get_successors() const {
	return _successors;
}

IBlock::Precedents Block::get_precedents() const {
	return _precedents;
}

} // namespace cfg
