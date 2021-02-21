#include "./element.hpp"

using namespace std;

namespace cfg {

Element::Element(IElement::Value value, Cfg* cfg)
: _value(value)
, _cfg(cfg)
{}

} // namespace cfg
