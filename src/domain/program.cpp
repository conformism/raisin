#include "domain/program.hpp"
#include "domain/core/types.hpp"

namespace domain {

auto Program::insert_cfg(cfg::Cfg cfg)
	-> core::result::Result<cfg::Cfg*, Failures::INVALID_UUID, Failures::ALREADY_INSIDE> {
	return _cfgs.insert(cfg.get_uuid(), cfg);
};
auto Program::remove_cfg(core::Uuid uuid)
	-> core::result::Result<bool, Failures::INVALID_UUID, Failures::NOT_INSIDE> {
	return _cfgs.remove(uuid);
};

auto Program::get_cfg_by_uuid(core::Uuid uuid)
	-> core::result::Result<cfg::Cfg*, Failures::INVALID_UUID, Failures::NOT_INSIDE> {
	return _cfgs.at(uuid);
};
}  // namespace domain
