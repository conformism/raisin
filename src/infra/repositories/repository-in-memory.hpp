#pragma once

#include "domain/cfg/cfg.hpp"
#include "domain/irepostory.hpp"

template<class Concrete, class Cfg, class CfgParserService>
class RespositoryInMemory : public IRespository<Cfg> {
public:
	using Cfgs = typename IRespository<Cfg>::Cfgs;

	auto readCfgs() -> Cfgs override {
		_cgfs = _cfg_parser_service.run();
		return _cgfs;
	};
	auto saveCfgs(Cfgs cfgs) -> void override{};

private:
	Cfgs const _cgfs;
	CfgParserService _cfg_parser_service;
};
