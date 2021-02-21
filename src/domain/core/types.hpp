#pragma once
#include <string>
#include <map>
#include <memory>

namespace core {
using Uuid = std::string;

template<class T>
using Aggregator = std::map<Uuid, T*>;

template<class T>
using Compositor = std::map<Uuid, std::unique_ptr<T>>;
template<typename T>
struct Result {
	int returnCode = 0;
	T&& reference = nullptr; // TODO: check that `&&` shit: Rvalue/LValue
};

}
