#pragma once

#include "domain/core/types.hpp"
#include "domain/cfg/cfg.hpp"

namespace domain {

class Program : public core::Entity {
public:
	using Cfgs = core::Compositor<cfg::Cfg>;

	[[nodiscard]] auto insert_cfg(cfg::Cfg cfg) -> core::result::
		Result<cfg::Cfg*, Failures::INVALID_UUID, Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto remove_cfg(core::Uuid uuid)
		-> core::result::Result<bool, Failures::INVALID_UUID, Failures::NOT_INSIDE>;
	[[nodiscard]] auto get_cfg_by_uuid(core::Uuid uuid)
		-> core::result::Result<cfg::Cfg*, Failures::INVALID_UUID, Failures::NOT_INSIDE>;

private:
	Cfgs _cfgs;
};
}  // namespace domain
