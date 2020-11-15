#pragma once

#include <memory>
#include <string>

namespace cfg {

class Cfg;

//******************************************************************************
class Element {
public:
	std::string str;
	Cfg* definition; // TODO: map table ?

	Element(std::string _str);
};

} // namesapce cfg
