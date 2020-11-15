#include "domain/cfg/block.hpp"

using namespace std;

namespace cfg {

//******************************************************************************
Block::Block(Block::Kind const _kind)
: kind(_kind)
{}

// Depending on kind, merge and output elements' texts;
//******************************************************************************
string Block::get_text() const {
}

} // namespace cfg
