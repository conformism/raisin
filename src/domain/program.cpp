#include "domain/program.hpp"

namespace domain {

using namespace core;

auto Program::insert_cfg(cfg::Cfg cfg)
	-> core::result::Result<cfg::Cfg*, result::Failures::ALREADY_INSIDE> {
	return _cfgs.insert(cfg.get_uuid(), cfg).set_failures<result::Failures::ALREADY_INSIDE>().value();
};

auto Program::remove_cfg(core::Uuid uuid)
	-> core::result::Result<bool, result::Failures::INVALID_UUID, result::Failures::NOT_INSIDE> {
	return _cfgs.remove(uuid);
};

auto Program::get_cfg_by_uuid(core::Uuid uuid)
	-> core::result::Result<cfg::Cfg*, result::Failures::INVALID_UUID, result::Failures::NOT_INSIDE> {
	return _cfgs.at(uuid);
};

}  // namespace domain
