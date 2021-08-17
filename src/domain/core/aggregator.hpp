#pragma once

#include "./guard.hpp"
#include "./result.hpp"
#include "./types.hpp"

#include <map>
#include <utility>

namespace core {

template<class T>
class Aggregator {
public:
	auto insert_or_assign(Uuid uuid, T* value) -> result::
		Result<result::Success<T*>, result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> {
		auto const result_guard = guard::is_null_pointer<T>(value);
		if (result_guard.is_success()) {
			// WTF
			// std::map<Uuid, T*> _aggregataaaa;
			// _aggregataaaa.insert(std::pair<Uuid, T*>(uuid, value));
			// std::pair<Uuid, T*> pair = std::pair<Uuid, T*>(uuid, value);
			_aggregated.insert_or_assign(std::pair<Uuid, T*>(uuid, value));
		}

		return result_guard;
	};

	[[nodiscard]] auto remove(Uuid const& uuid) -> result::
		Result<result::Success<Uuid>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> {
		auto const result_guard = at(uuid, *_aggregated).is_success();
		if (result_guard.is_failure()) {
			return result_guard;
		}
		_aggregated.erase(uuid);
		return result::
			Result<result::Success<Uuid>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>>(
				result::Success<Uuid>{uuid});
	};

	[[nodiscard]] auto count(Uuid const& uuid) const -> int {
		return _aggregated.count(uuid);
	};

	[[nodiscard]] auto is_inside(Uuid const& uuid) const -> bool {
		auto const is_contains_this_uuid = _aggregated.count(uuid) > 0;
		return is_contains_this_uuid;
	};

	[[nodiscard]] auto at(Uuid const& uuid) const -> result::
		Result<result::Success<T*>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> {
		bool const is_contains_this_uuid = _aggregated.count(uuid) > 0;
		if (is_contains_this_uuid) {
			return result::Result<
				result::Success<T*>,
				result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>>(
				result::Success<T*>{_aggregated.at(uuid)});
		}

		std::string reason = "No Contained at uuid: " + uuid + " is not present into collection.";

		auto const failure = result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>(reason);
		return result::
			Result<result::Success<T*>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>>(
				failure);
	};

private:
	// keep this private, it's an adaptater
	// https://en.wikipedia.org/wiki/Adapter_pattern
	// If some map methods are missing, please implement then into aggregator using result object.
	std::unordered_map<Uuid, T*> const _aggregated;
};

}  // namespace core
