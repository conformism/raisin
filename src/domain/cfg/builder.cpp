#include <catch2/catch_all.hpp>

#include <memory>
#include <utility>

#include "./cfg.hpp"

namespace cfg {

auto Cfg::Builder::set_uuid(Uuid uuid) -> result::
	Result<result::Success<Cfg::Builder&>, result::BasicFailure<Failures::INVALID_UUID>> {
	auto const result = guard::is_valid_uuid(uuid);
	if (result.is_failure()) {
		return result::
			Result<result::Success<Cfg::Builder&>, result::BasicFailure<Failures::INVALID_UUID>>(
				result.get_failure().value());
	}
	_uuid = uuid;
	return result::
		Result<result::Success<Cfg::Builder&>, result::BasicFailure<Failures::INVALID_UUID>>(
			result::Success<Cfg::Builder&>{*this});
};

auto Cfg::Builder::add_block(Block* block) -> result::Result<
	result::Success<Cfg::Builder&>,
	result::BasicFailure<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>> {
	auto const insert_result = _blocks.insert(block->get_uuid(), block);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<Cfg::Builder&>,
			result::BasicFailure<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>>(
			insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<Cfg::Builder&>,
		result::BasicFailure<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>>(
		result::Success<Cfg::Builder&>{*this});
};
auto Cfg::Builder::add_scope(Scope* scope) -> result::Result<
	result::Success<Cfg::Builder&>,
	result::BasicFailure<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>> {
	auto const insert_result = _scopes.insert(scope->get_uuid(), scope);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<Cfg::Builder&>,
			result::BasicFailure<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>>(
			insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<Cfg::Builder&>,
		result::BasicFailure<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>>(
		result::Success<Cfg::Builder&>{*this});
};

auto Cfg::Builder::build() -> Cfg {
	if (_uuid.empty()) {
		return Cfg(_blocks, _scopes);
	}

	return Cfg(_uuid, _blocks, _scopes);
};

}  // namespace cfg
