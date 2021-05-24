#pragma once

#include <memory>
#include <string>

#include "./ielement.hpp"

namespace cfg {

class Element: public IElement {
public:
	Element(IElement::Value value, ICfg* cfg);
	Value get_value();
	ICfg* get_cfg();
private:
	IElement::Value const _value;
	ICfg* const _cfg;
};

} // namesapce cfg
