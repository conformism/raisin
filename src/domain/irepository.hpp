#pragma once

#include "domain/core/compositor.hpp"
#include "domain/core/result.hpp"
#include "domain/core/types.hpp"

namespace domain {

using namespace core::result;

// TODO(dauliac) Use decorator design pattern If we need to have multiple databases
template<class Program>
class IRespository {
public:
	// TODO(dauliac) Maybe create dedicated aggregator cfgs class to have specific query
	//   search, order by, etc...
	// TODO(dauliac) version cfgs using file system hash
	virtual auto write(Program program) -> void = 0;
	[[nodiscard]] virtual auto read() -> Program* = 0;
};

}  // namespace domain
