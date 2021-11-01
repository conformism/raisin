#pragma once

#include "domain/cfg/cfg.hpp"
#include "domain/irepostory.hpp"

template<class Concrete, class Cfg, class CfgParserService>
class RespositoryInMemory : public IRespository<Cfg> {
public:
	using Cfgs = typename IRespository<Cfg>::Cfgs;

	auto readCfgs() -> Cfgs override {
		// TODO(dauliac) Use hash to knows if services need to run
		// const bool needs_to_refresh = _cfg_parser_service.is_changed();
		const bool needs_to_refresh = true;
		if (needs_to_refresh) {
			_cgfs = _cfg_parser_service.run();
		}

		return _cgfs;
	};
	auto saveCfgs(Cfgs cfgs) -> void override;

private:
	Cfgs const _cgfs;
	CfgParserService _cfg_parser_service;
};
