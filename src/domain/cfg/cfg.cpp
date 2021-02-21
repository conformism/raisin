#include "./cfg.hpp"

using namespace std;

namespace cfg {

Cfg::Cfg(IElement* element , ICfg::Blocks blocks, ICfg::Scopes scopes)
: _element(element)
, _blocks(std::move(blocks))
, _scopes(std::move(scopes))
{}

} // namespace cfg
