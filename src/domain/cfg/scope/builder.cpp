#include "domain/core/guard.hpp"
#include "scope.hpp"

namespace cfg {
auto Scope::Builder::set_uuid(Uuid uuid) -> result::Result<Builder*, Failures::INVALID_UUID> {
	constexpr auto success = result::success<Builder*, Failures::INVALID_UUID>;
	constexpr auto failure = result::failure<Builder*, Failures::INVALID_UUID>;

	auto const result = guard::is_valid_uuid(uuid);
	if (result.is_failure()) {
		return failure();
	}
	this->_uuid = uuid;
	return success(this);
};

auto Scope::Builder::add_child(Scope* child)
	-> result::Result<Scope::Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> {
	constexpr auto success =
		result::success<Scope::Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	constexpr auto failure_no_resource = result::
		failure<Builder*, Failures::NO_RESOURCES, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	constexpr auto failure_already_inside = result::
		failure<Builder*, Failures::NO_RESOURCES, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;

	auto const insert_result = _childs.insert(child->get_uuid(), child);
	if (insert_result.is_failure()) {
		// TODO(dauliac) find way to create union
		// TODO(dauliac) bad battern change it
		return insert_result.get_failure().value() == Failures::NO_RESOURCES
			? failure_no_resource()
			: failure_already_inside();
	}

	return success(this);
};

auto Scope::Builder::set_parent(Scope* parent)
	-> result::Result<Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> {
	constexpr auto success =
		result::success<Scope::Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	constexpr auto failure_no_resource = result::
		failure<Builder*, Failures::NO_RESOURCES, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	constexpr auto failure_already_inside = result::
		failure<Builder*, Failures::NO_RESOURCES, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;

	auto const result = guard::is_null_pointer(parent);
	if (result.is_failure()) {
		return failure_no_resource();
	}
	if (_parent == parent) {
		return failure_already_inside();
	}
	_parent = parent;
	return success(this);
};

auto Scope::Builder::add_block(Block* block)
	-> result::Result<Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> {
	constexpr auto success =
		result::success<Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	constexpr auto failure_no_resource = result::
		failure<Builder*, Failures::NO_RESOURCES, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	constexpr auto failure_already_inside = result::failure<
		Builder*,
		Failures::ALREADY_INSIDE,
		Failures::NO_RESOURCES,
		Failures::ALREADY_INSIDE>;

	auto const insert_result = _blocks.insert(block->get_uuid(), block);
	if (insert_result.is_failure()) {
		// TODO(dauliac) find way to create union
		// TODO(dauliac) bad battern change it
		return insert_result.get_failure().value() == Failures::NO_RESOURCES
			? failure_no_resource()
			: failure_already_inside();
	}
	return success(this);
};

[[nodiscard]] auto Scope::Builder::build() -> Scope {
	if (_uuid.empty()) {
		return Scope(_parent, std::move(_childs), std::move(_blocks));
	};
	return Scope(_uuid, _parent, std::move(_childs), std::move(_blocks));
}

}  // namespace cfg
