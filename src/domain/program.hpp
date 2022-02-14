#pragma once

#include "domain/core/types.hpp"
#include "domain/cfg/cfg.hpp"
#include <memory>

namespace domain {

using namespace core;

class Program : public core::Entity {
public:
	using Cfgs = core::Compositor<cfg::Cfg>;

	[[nodiscard]] auto insert_cfg(cfg::Cfg cfg) -> core::result::
		Result<cfg::Cfg*, core::result::Failures::ALREADY_INSIDE>;
	[[nodiscard]] auto remove_cfg(core::Uuid uuid)
		-> core::result::Result<bool, core::result::Failures::INVALID_UUID, core::result::Failures::NOT_INSIDE>;
	[[nodiscard]] auto get_cfg_by_uuid(core::Uuid uuid)
		-> core::result::Result<cfg::Cfg*, core::result::Failures::INVALID_UUID, core::result::Failures::NOT_INSIDE>;

private:
	std::unique_ptr<file::Language> const language;
	Cfgs _cfgs;
};
}  // namespace domain
