#pragma once

#include <list>

#include "domain/core/compositor.hpp"
#include "domain/core/result.hpp"
#include "domain/core/types.hpp"

namespace domain {

template<class Cfg>
class IProgram {
public:
	using Cfgs = core::Compositor<Cfg>;
	[[nodiscard]] virtual auto insert_cfg(Cfg cfg)
		-> core::result::Result<Cfg*, Failures::INVALID_UUID, Failures::ALREADY_INSIDE> = 0;
	[[nodiscard]] virtual auto remove_cfg(core::Uuid uuid)
		-> core::result::Result<bool, Failures::INVALID_UUID, Failures::NOT_INSIDE> = 0;
	[[nodiscard]] virtual auto get_cfg_by_uuid(core::Uuid uuid)
		-> core::result::Result<Cfg*, Failures::INVALID_UUID, Failures::NOT_INSIDE> = 0;
};
}  // namespace domain
