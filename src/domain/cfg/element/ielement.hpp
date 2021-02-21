#pragma once

#include <string>

namespace cfg {

class Cfg;

class IElement {
public:
	using Value = std::string;

	virtual Value get_value() = 0;
	virtual Cfg* get_cfg() = 0;
};

} // namesapce cfg
