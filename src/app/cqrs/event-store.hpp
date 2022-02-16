#pragma once

#include "icqrs.hpp"

#include <memory>
#include <queue>

namespace app::cqrs {

class SynchroneEventStore: public IEventStore {
public:
	auto run() -> void override;

private:
	std::queue<std::unique_ptr<IQuery>> _queries;
};

} // namespace app::cqrs
