#pragma once

#include "domain/core/aggregator.hpp"
#include "infra/services/iservice.hpp"

namespace infra::services::cfg {

template<class Cfg>
// TODO(dauliac) Replace void with Result
class ICfgParser : IService<void> {
public:
	using Cfgs = domain::core::Aggregator<Cfg>;
};

}  // namespace infra::services::cfg
