#pragma once

#include "domain/cfg/cfg.hpp"
#include "iprogram.hpp"

namespace domain {

class Program : public IProgram<cfg::Cfg> {
public:
	[[nodiscard]] auto insert_cfg(cfg::Cfg cfg) -> core::result::
		Result<cfg::Cfg*, Failures::INVALID_UUID, Failures::ALREADY_INSIDE> override;
	[[nodiscard]] auto remove_cfg(core::Uuid uuid)
		-> core::result::Result<bool, Failures::INVALID_UUID, Failures::NOT_INSIDE> override;
	[[nodiscard]] auto get_cfg_by_uuid(core::Uuid uuid)
		-> core::result::Result<cfg::Cfg*, Failures::INVALID_UUID, Failures::NOT_INSIDE> override;

private:
	IProgram::Cfgs _cfgs;
};
}  // namespace domain
