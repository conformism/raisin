#pragma once


namespace domain::core::result {
enum class Failures {
	UNKNOWN = 0,
	NOTHING,
	NO_RESOURCES,
	NOT_INSIDE,
	ALREADY_INSIDE,
	ALREADY_SETTED,
	CANT_HAVE_ZERO_LENGTH,
	INVALID_UUID,
};
} // namespace domain::core::result
