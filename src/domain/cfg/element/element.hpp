#pragma once

#include <memory>
#include <string>

#include "./ielement.hpp"

namespace cfg {

class Element: public IElement {
public:
	Element(IElement::Value value, Cfg* cfg);
	Cfg * get_cfg() override;
	Value get_value() override;
private:
	IElement::Value const _value;
	Cfg* const _cfg;
};

} // namesapce cfg
