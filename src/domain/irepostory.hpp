#pragma once

#include "domain/core/aggregator.hpp"

template<class Cfg>
class IRespository {
public:
	using Cfgs = domain::core::Aggregator<Cfg>;

	// TODO(dauliac) version cfgs using file system hash
	virtual auto readCfgs() -> Cfgs = 0;
	// TODO(dauliac) implements Result
	virtual auto saveCfgs(Cfgs cfgs) -> void = 0;
	// TODO(dauliac) implements snaphot with Memento
};
