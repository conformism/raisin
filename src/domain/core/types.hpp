#pragma once
#include <variant>
#include <string>
#include <map>
#include <memory>

namespace core {
using Uuid = std::string;

template<class T>
using Aggregator = std::map<Uuid, std::shared_ptr<T>>;

template<class T>
using Compositor = std::map<Uuid, std::unique_ptr<T>>;

}  // namespace core
