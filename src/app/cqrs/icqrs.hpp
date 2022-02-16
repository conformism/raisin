#pragma once

namespace app::cqrs {

class IEventStore {
public:
	virtual auto run() -> void;
};

class IQuery {
public:
	virtual auto run() -> void;
};

class ICommand : public IQuery {
};

} // namespace app::cqrs
