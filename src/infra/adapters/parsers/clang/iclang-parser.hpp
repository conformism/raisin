#pragma once

#include "infra/adapters/iadapter.hpp"

namespace infra::adapters::parser::clang {

// TODO(dauliac) Replace void with Result
class IClangParser : IAdapter<void> {
public:
};

}  // namespace infra::adapters::parser::clang
