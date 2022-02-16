#include "event-store.hpp"

namespace app::cqrs {

auto SynchroneEventStore::run() -> void {
	_queries.front()->run();
	_queries.pop();
};

} // namespace app::cqrs
