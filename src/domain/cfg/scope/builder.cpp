#include "domain/core/guard.hpp"
#include "scope.hpp"

namespace cfg {
auto Scope::Builder::set_uuid(Uuid uuid) -> result::
	Result<result::Success<Builder&>, result::BasicFailure<Failures::INVALID_UUID>> {
	auto const result = guard::is_valid_uuid(uuid);
	if (result.is_failure()) {
		return result::Result<
			result::Success<Builder&>,
			result::BasicFailure<Failures::INVALID_UUID>>(
			result.get_failure().value());
	}
	this->_uuid = uuid;
	return result::Result<
		result::Success<Builder&>,
		result::BasicFailure<Failures::INVALID_UUID>>(
		result::Success<Builder&>{*this});
};

auto Scope::Builder::add_child(Scope* child) -> result::Result<
	result::Success<Builder&>,
	result::
		BasicFailure<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>> {
	auto const insert_result = _childs.insert(child->get_uuid(), child);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<Builder&>,
			result::BasicFailure<
				Failures::NO_RESOURCES,
				Failures::ALREADY_INSIDE>>(insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<Builder&>,
		result::BasicFailure<
			Failures::NO_RESOURCES,
			Failures::ALREADY_INSIDE>>(result::Success<Builder&>{*this});
};

auto Scope::Builder::set_parent(Scope* parent) -> result::Result<
	result::Success<Scope::Builder&>,
	result::
		BasicFailure<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>> {
	auto const result = guard::is_null_pointer(parent);
	if (result.is_failure()) {
		return result::Result<
			result::Success<Scope::Builder&>,
			result::BasicFailure<
				Failures::NO_RESOURCES,
				Failures::ALREADY_INSIDE>>(
			result::BasicFailure<
				Failures::NO_RESOURCES,
				Failures::ALREADY_INSIDE>::
				create<Failures::NO_RESOURCES>());
	}
	if (_parent == parent) {
		return result::Result<
			result::Success<Builder&>,
			result::BasicFailure<
				Failures::NO_RESOURCES,
				Failures::ALREADY_INSIDE>>(
			result::BasicFailure<
				Failures::NO_RESOURCES,
				Failures::ALREADY_INSIDE>::
				create<Failures::ALREADY_INSIDE>());
	}
	_parent = parent;
	return result::Result<
		result::Success<Scope::Builder&>,
		result::BasicFailure<
			Failures::NO_RESOURCES,
			Failures::ALREADY_INSIDE>>(result::Success<Scope::Builder&>{*this});
};

auto Scope::Builder::add_block(Block* block) -> result::Result<
	result::Success<Builder&>,
	result::
		BasicFailure<Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>> {
	auto const insert_result = _blocks.insert(block->get_uuid(), block);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<Builder&>,
			result::BasicFailure<
				Failures::NO_RESOURCES,
				Failures::ALREADY_INSIDE>>(insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<Builder&>,
		result::BasicFailure<
			Failures::NO_RESOURCES,
			Failures::ALREADY_INSIDE>>(result::Success<Builder&>{*this});
};

[[nodiscard]] auto Scope::Builder::build() -> Scope {
	if (_uuid.empty()) {
		return Scope(_parent, std::move(_childs), std::move(_blocks));
	};
	return Scope(_uuid, _parent, std::move(_childs), std::move(_blocks));
}

}  // namespace cfg
