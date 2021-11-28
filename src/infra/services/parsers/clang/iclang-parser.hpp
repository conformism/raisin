#pragma once

#include "domain/core/aggregator.hpp"
#include "infra/services/iservice.hpp"

namespace infra::services::parser::clang {

template<class Cfg>
// TODO(dauliac) Replace void with Result
class IClangParser : IService<void> {
public:
};

}  // namespace infra::services::parser::clang
