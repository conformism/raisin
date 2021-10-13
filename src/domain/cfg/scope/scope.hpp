#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "../block/block.hpp"
#include "../block/iblock.hpp"
#include "iscope.hpp"

namespace cfg {

using namespace core;

class Scope : public IScope<Scope, Block> {
public:
	[[nodiscard]] auto is_root() const -> bool override;
	[[nodiscard]] auto has_childs() const -> bool override;
	[[nodiscard]] auto get_blocks() const -> Blocks override;
	[[nodiscard]] auto get_childs() const -> Childs override;
	[[nodiscard]] auto get_parent() const -> Parent override;
	class Builder;
	friend IBuilder<Builder>;

private:
	Scope(Parent parent, Childs childs, Blocks blocks);
	Scope(core::Uuid uuid, Parent parent, Childs childs, Blocks blocks);

	const Parent _parent;
	const Blocks _blocks;
	const Childs _childs;
};

class Scope::Builder : public IScope::IBuilder<Builder> {
public:
	auto set_uuid(Uuid uuid) -> result::Result<Builder&, Failures::INVALID_UUID> override;
	auto add_child(Scope* child)
		-> result::Result<Builder&, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> override;
	auto set_parent(Scope* parent)
		-> result::Result<Builder&, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> override;
	auto add_block(Block* block)
		-> result::Result<Builder&, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> override;
	[[nodiscard]] auto build() -> Scope override;

private:
	Uuid _uuid;
	Scope* _parent;
	Aggregator<Scope> _childs;
	Aggregator<Block> _blocks;
};

}  // namespace cfg
