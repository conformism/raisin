#include <memory>
#include <utility>

#include "./block.hpp"

namespace domain::cfg {

auto Block::Builder::set_uuid(Uuid uuid) -> result::Result<Builder*, Failures::INVALID_UUID> {
	constexpr auto success = result::success<Builder*, Failures::INVALID_UUID>;
	constexpr auto failure = result::failure<Builder*, Failures::INVALID_UUID>;

	auto const result = guard::is_valid_uuid(uuid);
	if (result.is_failure()) {
		return failure();
	}
	_uuid = uuid;
	return success(this);
};

auto Block::Builder::set_text(std::string text) -> Builder* {
	_text = std::move(text);
	return this;
};

auto Block::Builder::add_precedent(Block* precedent)
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

	// Assume that uuid is valid
	auto const insert_result = _precedents.insert(precedent->get_uuid(), precedent);
	if (insert_result.is_failure()) {
		// TODO(dauliac) find way to create union
		return insert_result.get_failure().value() == Failures::NO_RESOURCES
			? failure_no_resource()
			: failure_already_inside();
	}
	return success(this);
};
auto Block::Builder::add_successor(Block* successor)
	-> result::Result<Block::Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> {
	constexpr auto success =
		result::success<Block::Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	constexpr auto failure_no_resource = result::failure<
		Block::Builder*,
		Failures::NO_RESOURCES,
		Failures::NO_RESOURCES,
		Failures::ALREADY_INSIDE>;
	constexpr auto failure_already_inside = result::failure<
		Block::Builder*,
		Failures::ALREADY_INSIDE,
		Failures::NO_RESOURCES,
		Failures::ALREADY_INSIDE>;

	// Assume that uuis is valid
	auto const insert_result = _successors.insert(successor->get_uuid(), successor);
	if (insert_result.is_failure()) {
		// TODO(dauliac) find way to create union
		return insert_result.get_failure().value() == Failures::NO_RESOURCES
			? failure_no_resource()
			: failure_already_inside();
	}

	return success(this);
};

auto Block::Builder::build() -> Block {
	if (_uuid.empty()) {
		return Block(_precedents, _successors);
	}

	return Block(_uuid, _precedents, _successors);
};

}  // namespace domain::cfg
