#pragma once

#include "./guard.hpp"
#include "./result.hpp"
#include "./types.hpp"

#include <unordered_map>
#include <utility>

namespace domain::core {

template<class T>
class Compositor {
public:
	[[nodiscard]] auto size() const -> int {
		return _composed.empty();
	}
	[[nodiscard]] auto empty() const -> bool {
		return _composed.empty();
	}

	[[nodiscard]] auto is_inside(Uuid const& uuid) const -> bool {
		auto const is_contains_this_uuid = _composed.count(uuid) > 0;
		return is_contains_this_uuid;
	}

	[[nodiscard]] auto count(Uuid const& uuid) const -> int {
		return _composed.count(uuid);
	}

	[[nodiscard]] auto at(Uuid const& uuid) const
		-> result::Result<T*, Failures::INVALID_UUID, Failures::NOT_INSIDE> {
		constexpr auto success = result::success<T*, Failures::INVALID_UUID, Failures::NOT_INSIDE>;
		constexpr auto failure_invalid_uuid = result::
			failure<T*, Failures::INVALID_UUID, Failures::INVALID_UUID, Failures::NOT_INSIDE>;
		constexpr auto failure_not_inside =
			result::failure<T*, Failures::NOT_INSIDE, Failures::INVALID_UUID, Failures::NOT_INSIDE>;

		auto const guard_uuid = guard::is_valid_uuid(uuid);
		if (guard_uuid.is_failure()) {
			return failure_invalid_uuid();
		}

		bool const is_contains_this_uuid = _composed.count(uuid) > 0;
		if (is_contains_this_uuid) {
			// Obligation to use intermediate variable for strings or other types likes
			return success(_composed.at(uuid).get());
		}

		return failure_not_inside();
	}

	[[nodiscard]] auto remove(Uuid const& uuid)
		-> result::Result<bool, Failures::INVALID_UUID, Failures::NOT_INSIDE> {
		constexpr auto success =
			result::success<bool, Failures::INVALID_UUID, Failures::NOT_INSIDE>;

		auto const result_guard = at(uuid);
		if (result_guard.is_success()) {
			_composed.erase(uuid);
			return result_guard.template set_success<bool>(true);
		}
		return result_guard.template set_success<bool>(false);
	}

	[[nodiscard]] auto insert(Uuid uuid, T value)
		-> result::Result<T*, Failures::INVALID_UUID, Failures::ALREADY_INSIDE> {
		constexpr auto success =
			result::success<T*, Failures::INVALID_UUID, Failures::ALREADY_INSIDE>;
		constexpr auto failure_invalid_uuid = result::
			failure<T*, Failures::INVALID_UUID, Failures::INVALID_UUID, Failures::ALREADY_INSIDE>;
		constexpr auto failure_already_inside = result::
			failure<T*, Failures::ALREADY_INSIDE, Failures::INVALID_UUID, Failures::ALREADY_INSIDE>;

		auto const guard_uuid = guard::is_valid_uuid(uuid);
		if (guard_uuid.is_failure()) {
			// TODO(dauliac) find way to have combine working
			// return guard_uuid
			//     .combine_failures<T, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>();
			return failure_invalid_uuid();
		}

		// TODO(dauliac) add tests, units tests not fails if false is hardcoded here
		if (is_inside(uuid)) {
			return failure_already_inside();
		}
		// _composed.insert(uuid, value);
		_composed.insert_or_assign(uuid, std::make_unique<T>(value));

		return success(_composed.at(uuid).get());
	}

private:
	// keep this private, it's an adaptater
	// https://en.wikipedia.org/wiki/Adapter_pattern
	// If some map methods are missing, please implement then into aggregator using result object.
	std::unordered_map<Uuid, std::unique_ptr<T>> _composed;
};

}  // namespace domain::core
