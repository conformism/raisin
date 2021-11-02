#pragma once

#include <string>

namespace domain::cfg {

class IElement {
public:
	using Value = std::string;

	virtual Value get_value() = 0;
	// virtual ICfg* get_cfg() = 0;
};

}  // namespace domain::cfg
