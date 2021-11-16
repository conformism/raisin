#pragma once

#include "domain/core/aggregator.hpp"
#include "infra/services/iservice.hpp"

namespace infra::services::cfg {

template<class Cfg>
class ICfgParser : IService<domain::core::Aggregator<Cfg>> {
public:
	using Cfgs = domain::core::Aggregator<Cfg>;
	virtual auto run() -> Cfgs = 0;
};

}  // namespace infra::services::cfg
