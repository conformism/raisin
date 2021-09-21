#pragma once

enum class BasicFailureRegistrar {
	NOTHING = 0,
	NO_RESOURCES,
	NOT_INSIDE,
	ALREADY_INSIDE,
	ALREADY_SETTED,
	CANT_HAVE_ZERO_LENGTH,
	INVALID_UUID,
};
using Err = BasicFailureRegistrar;
