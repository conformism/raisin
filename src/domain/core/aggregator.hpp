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
	[[nodiscard]] auto is_inside(Uuid const& uuid) const -> bool {
		auto const is_contains_this_uuid = _aggregated.count(uuid) > 0;
		return is_contains_this_uuid;
	};

	[[nodiscard]] auto count(Uuid const& uuid) const -> int {
		return _aggregated.count(uuid);
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

	auto insert_or_assign(Uuid uuid, T* value) -> result::
		Result<result::Success<T*>, result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> {
		auto const result_guard = guard::is_null_pointer<T>(value);
		if (result_guard.is_success()) {
			// WTF
			// std::map<Uuid, T*> _aggregataaaa;
			// _aggregataaaa.insert(std::pair<Uuid, T*>(uuid, value));
			// std::pair<Uuid, T*> pair = std::pair<Uuid, T*>(uuid, value);
			_aggregated.insert_or_assign(uuid, value);
		}

		return result_guard;
	};

	[[nodiscard]] auto remove(Uuid const& uuid) -> result::
		Result<result::Success<T*>, result::BasicFailure<BasicFailureRegistrar::NOT_INSIDE>> {
		auto const result_guard = at(uuid);
		if (result_guard.is_success()) {
			_aggregated.erase(uuid);
		}

		return result_guard;
	};

	[[nodiscard]] auto insert(Uuid uuid, T* value) -> std::variant<
		result::
			Result<result::Success<T*>, result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>,
		result::Result<
			result::Success<T*>,
			result::BasicFailure<BasicFailureRegistrar::ALREADY_INSIDE>>> {
		auto const result_guard = guard::is_null_pointer<T>(value);
		if (result_guard.is_failure()) {
			return result_guard;
		}
		if (is_inside(uuid)) {
			result::Result<
				result::Success<T*>,
				result::BasicFailure<BasicFailureRegistrar::ALREADY_INSIDE>>(
				result::BasicFailure<BasicFailureRegistrar::ALREADY_INSIDE>(
					"The inserted uuid is already present in."));
		}
		_aggregated.insert(uuid, value);

		result::Result<
			result::Success<T*>,
			result::BasicFailure<BasicFailureRegistrar::ALREADY_INSIDE>>(
			result::Success<T*>(value));
	}

private:
	// keep this private, it's an adaptater
	// https://en.wikipedia.org/wiki/Adapter_pattern
	// If some map methods are missing, please implement then into aggregator using result object.
	std::unordered_map<Uuid, T*> _aggregated{};
};

}  // namespace core
