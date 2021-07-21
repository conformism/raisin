#pragma once

#include <map>
#include <vector>

#include "../../core/types.hpp"

namespace cfg {

using namespace core;

template<class Concrete, class ConcreteBlock>
class IScope : public Entity {
public:
	using Parent = Concrete*;
	using Blocks = core::Aggregator<ConcreteBlock>;
	using Childs = core::Aggregator<Concrete>;

	explicit IScope(core::Uuid uuid) : Entity(std::move(uuid)){};
	[[nodiscard]] virtual auto get_blocks() const -> Blocks = 0;
	[[nodiscard]] virtual auto get_childs() const -> Childs = 0;
	[[nodiscard]] virtual auto get_parent() const -> Parent = 0;
};

}  // namespace cfg
