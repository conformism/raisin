#pragma once

#include <string>
#include <map>
#include "../../core/types.hpp"

namespace cfg {

class IBlock {
public:
	using Uuid = core::Uuid;
	// enum Kind {};
	using Result = core::Result<IBlock>;
	using Precedents = core::Aggregator<IBlock>;
	using Successors = core::Aggregator<IBlock>;

	virtual ~IBlock() = default;
	virtual Uuid get_uuid() const = 0;
	virtual bool is_entry() const = 0;
	virtual bool is_exit() const = 0;
	virtual std::string get_text() const = 0;
	// virtual Kind get_kind() const = 0;
	virtual Successors get_successors() const = 0;
	virtual Precedents get_precedents() const = 0;
};

} // namespace cfg
