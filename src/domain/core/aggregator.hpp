#pragma once

#include "./guard.hpp"
#include "./result.hpp"
#include "./types.hpp"

#include <unordered_map>
#include <utility>

namespace core {

template<class T>
class Aggregator {
public:
	[[nodiscard]] auto size() const -> int {
		return _aggregated.empty();
	}
	[[nodiscard]] auto empty() const -> bool {
		return _aggregated.empty();
	}

	[[nodiscard]] auto is_inside(Uuid const& uuid) const -> bool {
		auto const is_contains_this_uuid = _aggregated.count(uuid) > 0;
		return is_contains_this_uuid;
	}

	[[nodiscard]] auto count(Uuid const& uuid) const -> int {
		return _aggregated.count(uuid);
	}

	[[nodiscard]] auto at(Uuid const& uuid) const -> result::Result<T*, Failures::NOT_INSIDE> {
		constexpr auto success = result::success<T*, Failures::NOT_INSIDE>;
		constexpr auto failure = result::failure<T*, Failures::NOT_INSIDE>;

		bool const is_contains_this_uuid = _aggregated.count(uuid) > 0;
		if (is_contains_this_uuid) {
			return success(_aggregated.at(uuid));
		}

		return failure();
	}

	[[nodiscard]] auto remove(Uuid const& uuid) -> result::Result<T*, Failures::NOT_INSIDE> {
		auto const result_guard = at(uuid);
		if (result_guard.is_success()) {
			_aggregated.erase(uuid);
		}

		return result_guard;
	}

	[[nodiscard]] auto insert(Uuid uuid, T* value)
		-> result::Result<T*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE> {
		constexpr auto success =
			result::success<T*, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
		constexpr auto failure_no_resource = result::
			failure<T*, Failures::NO_RESOURCES, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;
		constexpr auto failure_already_inside = result::
			failure<T*, Failures::NO_RESOURCES, Failures::NO_RESOURCES, Failures::ALREADY_INSIDE>;

		auto const result_guard = guard::is_null_pointer<T>(value);

		if (result_guard.is_failure()) {
			return failure_no_resource();
		}

		// TODO(dauliac) add tests, units tests not fails if false is hardcoded here
		if (is_inside(uuid)) {
			return failure_already_inside();
		}
		_aggregated.insert_or_assign(uuid, value);

		return success(value);
	}

private:
	// keep this private, it's an adaptater
	// https://en.wikipedia.org/wiki/Adapter_pattern
	// If some map methods are missing, please implement then into aggregator using result object.
	std::unordered_map<Uuid, T*> _aggregated;
};

}  // namespace core
