#include <memory>
#include <utility>

#include "./cfg.hpp"

namespace cfg {

auto Cfg::Builder::set_uuid(Uuid uuid) -> result::Result<
	result::Success<Cfg::Builder&>,
	result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> {
	auto const result = guard::is_valid_uuid(uuid);
	if (result.is_failure()) {
		return result::Result<
			result::Success<Cfg::Builder&>,
			result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
			result.get_failure().value());
	}
	_uuid = uuid;
	return result::Result<
		result::Success<Cfg::Builder&>,
		result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
		result::Success<Cfg::Builder&>{*this});
};

auto Cfg::Builder::add_block(Block* block) -> result::Result<
	result::Success<Cfg::Builder&>,
	result::
		BasicFailure<BasicFailureRegistrar::NO_RESOURCES, BasicFailureRegistrar::ALREADY_INSIDE>> {
	auto const insert_result = _blocks.insert(block->get_uuid(), block);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<Cfg::Builder&>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>>(insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<Cfg::Builder&>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>>(result::Success<Cfg::Builder&>{*this});
};
auto Cfg::Builder::add_scope(Scope* scope) -> result::Result<
	result::Success<Cfg::Builder&>,
	result::
		BasicFailure<BasicFailureRegistrar::NO_RESOURCES, BasicFailureRegistrar::ALREADY_INSIDE>> {
	auto const insert_result = _scopes.insert(scope->get_uuid(), scope);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<Cfg::Builder&>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>>(insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<Cfg::Builder&>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>>(result::Success<Cfg::Builder&>{*this});
};

auto Cfg::Builder::build() -> Cfg {
	if (_uuid.empty()) {
		// return Cfg(_is_exit, _is_exit, precedents, successors);
		return Cfg(_scopes, _blocks);
	}

	// return Cfg(_uuid, _is_exit, _is_exit, precedents, successors);
	return Cfg(_uuid, _precedents, _successors);
};

}  // namespace cfg