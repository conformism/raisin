#pragma once

#include "iconfig.hpp"
#include "infra/services/config/iconfig.hpp"

namespace infra::services::config {

class ConfigParser : IService<Cfgs> {
public:
	auto run() -> Iconfig;
};

}  // namespace infra::services::config
