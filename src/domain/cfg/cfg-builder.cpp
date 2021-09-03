#include "./cfg.hpp"
#include "domain/core/guard.hpp"
#include "domain/core/result.hpp"
#include <memory>

namespace cfg {

auto Cfg::Builder::set_uuid(core::Uuid uuid) -> result::Result<
	result::Success<ICfg::IBuilder*>,
	result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> {
	const auto is_uuid_valid_result = guard::is_valid_uuid(uuid);
	if (is_uuid_valid_result.is_failure()) {
		return result::Result<
			result::Success<ICfg::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
			result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>(
				is_uuid_valid_result.get_failure()->get_reason()));
	}

	_uuid = uuid;

	return result::Result<
		result::Success<ICfg::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
		result::Success<ICfg::IBuilder*>{this});
}

auto Cfg::Builder::add_block(Block* block) -> result::Result<
	result::Success<ICfg::IBuilder*>,
	result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> {
	auto const is_inserted = _blocks->insert_or_assign(block->get_uuid(), block);
	if (is_inserted.is_failure()) {
		return result::Result<
			result::Success<ICfg::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>(
				is_inserted.get_failure()->get_reason()));
	}

	return result::Result<
		result::Success<ICfg::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
		result::Success<ICfg::IBuilder*>{this});
}

auto Cfg::Builder::add_scope(Scope* scope) -> result::Result<
	result::Success<ICfg::IBuilder*>,
	result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> {
	auto const is_inserted = _scopes->insert_or_assign(scope->get_uuid(), scope);
	if (is_inserted.is_failure()) {
		return result::Result<
			result::Success<ICfg::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>(
				is_inserted.get_failure()->get_reason()));
	}

	return result::Result<
		result::Success<ICfg::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
		result::Success<ICfg::IBuilder*>{this});
}

auto Cfg::Builder::set_blocks(Aggregator<Block>* blocks) -> result::Result<
	result::Success<ICfg::IBuilder*>,
	result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> {
	const auto blocks_guard = guard::is_null_pointer(blocks);
	if (blocks_guard.is_failure()) {
		return result::Result<
			result::Success<ICfg::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>(
				blocks_guard.get_failure()->get_reason()));
	}

	_blocks = blocks;

	return result::Result<
		result::Success<ICfg::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
		result::Success<ICfg::IBuilder*>{this});
}

auto Cfg::Builder::set_scopes(Aggregator<Scope>* scopes) -> result::Result<
	result::Success<ICfg::IBuilder*>,
	result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> {
	const auto scopes_guard = guard::is_null_pointer(scopes);
	if (scopes_guard.is_failure()) {
		return result::Result<
			result::Success<ICfg::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>(
				scopes_guard.get_failure()->get_reason()));
	}

	_scopes = scopes;

	return result::Result<
		result::Success<ICfg::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
		result::Success<ICfg::IBuilder*>{this});
}

auto Cfg::Builder::build() -> Cfg {
	Cfg _builded = Cfg(_uuid, *_blocks, *_scopes);
	return _builded;
}
}  // namespace cfg
