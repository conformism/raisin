#include <memory>
#include <utility>

#include "./block.hpp"

namespace cfg {

auto Block::Builder::set_uuid(Uuid uuid) -> result::Result<
	result::Success<Block::Builder&>,
	result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> {
	auto const result = guard::is_valid_uuid(uuid);
	if (result.is_failure()) {
		return result::Result<
			result::Success<Block::Builder&>,
			result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
			result.get_failure().value());
	}
	_uuid = uuid;
	return result::Result<
		result::Success<Block::Builder&>,
		result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
		result::Success<Block::Builder&>{*this});
};

auto Block::Builder::set_text(std::string text) -> Builder& {
	_text = std::move(text);
	return *this;
};

auto Block::Builder::define_as_entry(bool is_entry) -> result::Result<
	result::Success<Block::Builder&>,
	result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>> {
	if (_is_entry == is_entry) {
		return result::Result<
			result::Success<Block::Builder&>,
			result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>>(
			result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>::create());
	}
	_is_entry = is_entry;
	return result::Result<
		result::Success<Block::Builder&>,
		result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>>(
		result::Success<Block::Builder&>{*this});
};

auto Block::Builder::define_as_exit(bool is_exit) -> result::Result<
	result::Success<Block::Builder&>,
	result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>> {
	if (_is_exit == is_exit) {
		return result::Result<
			result::Success<Block::Builder&>,
			result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>>(
			result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>::create());
	}
	_is_exit = is_exit;
	return result::Result<
		result::Success<Block::Builder&>,
		result::BasicFailure<BasicFailureRegistrar::ALREADY_SETTED>>(
		result::Success<Block::Builder&>{*this});
};

auto Block::Builder::add_precedent(Block* precedent) -> result::Result<
	result::Success<Block::Builder&>,
	result::
		BasicFailure<BasicFailureRegistrar::NO_RESOURCES, BasicFailureRegistrar::ALREADY_INSIDE>> {
	auto const insert_result = _precedents.insert(precedent->get_uuid(), precedent);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<Block::Builder&>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>>(insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<Block::Builder&>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>>(result::Success<Block::Builder&>{*this});
};
auto Block::Builder::add_successor(Block* successor) -> result::Result<
	result::Success<Block::Builder&>,
	result::
		BasicFailure<BasicFailureRegistrar::NO_RESOURCES, BasicFailureRegistrar::ALREADY_INSIDE>> {
	auto const insert_result = _precedents.insert(successor->get_uuid(), successor);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<Block::Builder&>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>>(insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<Block::Builder&>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>>(result::Success<Block::Builder&>{*this});
};

auto Block::Builder::build() -> Block {
	if (_uuid.empty()) {
		// return Block(_is_exit, _is_exit, precedents, successors);
		return Block(_precedents, _successors);
	}

	// return Block(_uuid, _is_exit, _is_exit, precedents, successors);
	return Block(_uuid, _precedents, _successors);
};

}  // namespace cfg
