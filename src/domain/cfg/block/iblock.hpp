#pragma once

#include <string>
#include <map>
#include "../../core/types.hpp"

namespace cfg {

class IBlock {
public:
	using Uuid = core::Uuid;
	// enum Kind {};
	using Precedents = core::Aggregator<IBlock>;
	using Successors = core::Aggregator<IBlock>;

	virtual ~IBlock() = default;
	virtual auto get_uuid() const -> Uuid = 0;
	virtual auto is_entry() const -> bool = 0;
	virtual auto is_exit() const -> bool = 0;
	virtual auto get_text() const -> std::string = 0;
	// virtual Kind get_kind() const = 0;
	virtual auto get_successors() const -> Successors const&  = 0;
	virtual auto get_precedents() const -> Precedents const&  = 0;
};

} // namespace cfg
