#pragma once

#include "domain/cfg/cfg.hpp"
#include "domain/core/types.hpp"
#include "infra/services/cfg/icfg-parser.hpp"

namespace infra::services::cfg {
class CfgParserMock : ICfgParser<domain::cfg::Cfg> {
public:
	using Cfg = domain::cfg::Cfg;
	using Cfgs = typename ICfgParser<domain::cfg::Cfg>::Cfgs;

	auto run() -> Cfgs override {
		return _cfgs;
	};
	auto mock() {
		// TODO(dauliac) Use mocking lib to change that ugly code
		auto builder = Cfg::Builder();
		Cfg cfg_1 = builder.build();
		Cfg cfg_2 = builder.build();
		const auto result = _cfgs.insert(cfg_1.get_uuid(), &cfg_1);
		const auto result_2 = _cfgs.insert(cfg_2.get_uuid(), &cfg_2);
		return result;
	};

private:
	Cfgs _cfgs;
};

}  // namespace infra::services::cfg
