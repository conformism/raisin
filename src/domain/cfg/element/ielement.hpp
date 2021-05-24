#pragma once

#include <string>

namespace cfg {

class ICfg;

class IElement {
public:
	using Value = std::string;

	virtual Value get_value() = 0;
	virtual ICfg* get_cfg() = 0;
};

} // namesapce cfg
