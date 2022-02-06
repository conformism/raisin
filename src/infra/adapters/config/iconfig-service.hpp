#pragma once

#include "iconfig.hpp"
#include "infra/services/config/iconfig.hpp"

namespace infra::adapters::config {

class ConfigParser : IAdapter<Cfgs> {
public:
	auto run() -> Iconfig;
};

}  // namespace infra::adapters::config
