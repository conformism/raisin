#include <catch2/catch_all.hpp>

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "domain/core/result.hpp"

using namespace core::result;

SCENARIO("Core Result system should be usable as success by value") {
	GIVEN("value variable based on random type") {
		int test_value = 2;
		WHEN("Result is created") {
			auto const result = Result<int>(test_value);
			THEN("The result object success should be queried") {
				REQUIRE(result.is_success() == true);
				REQUIRE(result.get_success() == test_value);
			}
			AND_THEN("The result object failure should not be queriable") {
				REQUIRE(result.is_failure() != true);
				REQUIRE(result.get_failure().has_value() == false);
			}
		}
	}
}

SCENARIO("Core Result system should be usable as success by pointer") {
	GIVEN("value variable based on random type") {
		int test_value = 2;
		int* test_ptr = &test_value;
		WHEN("Result is created") {
			auto const result = Result<int*>(test_ptr);
			THEN("The result object success should be queried") {
				REQUIRE(result.is_success() == true);
				REQUIRE(result.get_success().value() == test_ptr);
			}
			AND_THEN("The result object failure should not be queriable") {
				REQUIRE(result.is_failure() != true);
				REQUIRE(result.get_failure().has_value() == false);
			}
		}
	}
}

SCENARIO("Core Result system should be usable as failure") {
	GIVEN("Invalid operation") {
		int const* invalid_result = nullptr;
		WHEN("Result is created") {
			auto const result =
				Result<int, Failures::NO_RESOURCES>::create<Failures::NO_RESOURCES>();
			THEN("The result object failure should be queried") {
				REQUIRE(result.is_failure() == true);
				REQUIRE(result.get_failure() == Failures::NO_RESOURCES);
			}
			AND_THEN("The result object success should not be queriable") {
				REQUIRE(result.is_success() == false);
				REQUIRE(result.get_success().has_value() == false);
			}
		}
	}
}
