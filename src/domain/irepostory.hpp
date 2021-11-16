#pragma once

#include "domain/core/compositor.hpp"
#include "domain/core/result.hpp"
#include "domain/core/types.hpp"

namespace domain {

using namespace core::result;

template<class Cfg>
class IRespository {
public:
	// TODO(dauliac) Maybe create dedicated aggregator cfgs class to have specific query
	//   search, order by, etc...
	using Cfgs = core::Compositor<Cfg>;

	// TODO(dauliac) version cfgs using file system hash
	virtual auto save_cfgs(Cfgs cfgs) -> void = 0;
	[[nodiscard]] virtual auto update_cfg(Cfg cfg)
		-> Result<Cfg*, Failures::INVALID_UUID, Failures::NO_RESOURCES> = 0;
	[[nodiscard]] virtual auto get_cfg_by_id(core::Uuid cfg_uuid)
		-> Result<Cfg*, Failures::INVALID_UUID, Failures::NOT_INSIDE> = 0;
	// TODO(dauliac) implements Result
	// TODO(dauliac) implements snaphot with Memento
};

}  // namespace domain
