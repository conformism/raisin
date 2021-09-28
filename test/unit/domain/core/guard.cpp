#include <catch2/catch_all.hpp>

#include "domain/core/failure-registrar.hpp"
#include "domain/core/guard.hpp"

using namespace core;

SCENARIO("Guard against null pointer should works with valid pointer.") {
	GIVEN("Valid pointer.") {
		const int value_object = 1234;
		const int* ptr = &value_object;

		WHEN("Guard check the pointer.") {
			auto const result = guard::is_null_pointer<const int>(ptr);
			THEN("The result should be sucess.") {
				REQUIRE(result.is_success() == true);
				REQUIRE(result.get_success()->get_value() == ptr);
			}
		}
	}
}

SCENARIO("Guard against null ptr should works with invalid pointer.") {
	GIVEN("Valid pointer.") {
		const int* ptr = nullptr;

		WHEN("Guard check the pointer.") {
			auto const result = guard::is_null_pointer<const int>(ptr);
			THEN("The result should be sucess.") {
				REQUIRE(result.is_failure() == true);
				AND_THEN("The result failure value should say there is no resouces.") {
					REQUIRE(result.get_failure()->get_id() == Failures::NO_RESOURCES);
				}
			}
		}
	}
}
