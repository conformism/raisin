#pragma once

#include "domain/cfg/cfg.hpp"
#include "domain/core/types.hpp"
#include "domain/irepostory.hpp"
#include <memory>

namespace infra::repository {

template<class Cfg, class CfgParserService>
class RespositoryInMemory : public domain::IRespository<Cfg> {
public:
	using Cfgs = typename domain::IRespository<Cfg>::Cfgs;
	explicit RespositoryInMemory(std::unique_ptr<CfgParserService> cfg_parser_service)
		: _cfg_parser_service(cfg_parser_service){};

	auto save_cfgs(Cfgs cfgs) -> void override {
		_cfgs = cfgs;
	}

	auto update_cfg(Cfg cfg)
		-> domain::Result<Cfg*, Failures::INVALID_UUID, Failures::NO_RESOURCES> override {
		if (_cfgs.is_inside(cfg.get_uuid())) {
			_cfgs.remove(cfg.get_uuid());
		}
		auto const result_cfg = _cfgs.insert(cfg.get_uuid(), cfg);
		auto const result =
			result_cfg.template set_failures<Failures::INVALID_UUID, Failures::NO_RESOURCES>();
		return result.value();
	};

	auto get_cfg_by_id(domain::core::Uuid cfg_uuid) -> domain::core::result::
		Result<Cfg*, Failures::INVALID_UUID, Failures::NOT_INSIDE> override {
		return _cfgs.at(cfg_uuid);
	};

private:
	Cfgs _cfgs;
	std::unique_ptr<CfgParserService> _cfg_parser_service;
};
}  // namespace infra::repository
