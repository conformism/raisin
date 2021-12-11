#pragma once

#include <string>

#include "domain/core/types.hpp"

namespace domain::cfg {

class Element : public core::Entity {
public:
	// Element(IElement::Value value, ICfg* cfg);
	// Value get_value();
	// ICfg* get_cfg();

private:
	std::string _value;
	// ICfg* const _cfg;
};

}  // namespace domain::cfg
