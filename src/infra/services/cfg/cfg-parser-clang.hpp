#pragma once

#include "domain/core/aggregator.hpp"
#include "icfg-parser.hpp"

namespace infra::services::cfg {

template<class Cfg>
class CfgParserClang : ICfgParser<Cfg> {
public:
	auto run() -> typename ICfgParser<Cfg>::Cfgs{};
};

}  // namespace infra::services::cfg
