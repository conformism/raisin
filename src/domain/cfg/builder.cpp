#include <catch2/catch_all.hpp>

#include <memory>
#include <utility>

#include "./cfg.hpp"

namespace domain::cfg {

auto Cfg::Builder::set_uuid(Uuid uuid) -> result::Result<Builder*, Failures::INVALID_UUID> {
	constexpr auto success = result::success<Builder*, Failures::INVALID_UUID>;
	constexpr auto failure = result::failure<Builder*, Failures::INVALID_UUID>;

	auto const result = guard::is_valid_uuid(uuid);
	if (result.is_failure()) {
		return failure();
	}
	_uuid = uuid;
	return success(this);
};

auto Cfg::Builder::add_block(Block block)
	-> result::Result<Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> {
	constexpr auto success =
		result::success<Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	constexpr auto failure_already_inside = result::failure<
		Builder*,
		Failures::ALREADY_INSIDE,
		Failures::NO_RESOURCES,
		Failures::ALREADY_INSIDE>;

	auto const uuid = block.get_uuid();
	auto const insert_result = _blocks.insert(uuid, std::move(block));
	if (insert_result.is_failure()) {
		// TODO(dauliac) find way to create union
		return failure_already_inside();
	}
	return success(this);
};
auto Cfg::Builder::add_scope(Scope scope)
	-> result::Result<Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> {
	constexpr auto success =
		result::success<Builder*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
	constexpr auto failure_already_inside = result::failure<
		Builder*,
		Failures::ALREADY_INSIDE,
		Failures::NO_RESOURCES,
		Failures::ALREADY_INSIDE>;

	auto const uuid = scope.get_uuid();
	auto const insert_result = _scopes.insert(uuid, std::move(scope));
	if (insert_result.is_failure()) {
		// TODO(dauliac) find way to create union
		return failure_already_inside();
	}
	return success(this);
};

auto Cfg::Builder::build() -> Cfg {
	if (_uuid.empty()) {
		return Cfg(_blocks, _scopes);
	}

	return Cfg(_uuid, _blocks, _scopes);
};

}  // namespace domain::cfg
