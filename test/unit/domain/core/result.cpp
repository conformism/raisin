#include <catch2/catch_all.hpp>

#include "domain/core/result.hpp"

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

using namespace core::result;

SCENARIO("Core Result system should be usable as success by value") {
	GIVEN("value variable based on random type") {
		int test_value = 2;
		AND_GIVEN("Success to pass to result") {
			auto const sucess = Success<int>{test_value};
			WHEN("Result is created") {
				auto const result = Result<Success<int>>(sucess);
				THEN("The result object success should be queried") {
					REQUIRE(result.is_success() == true);
					REQUIRE(result.get_success()->get_value() == test_value);
				}
				AND_THEN("The result object failure should not be queriable") {
					REQUIRE(result.is_failure() != true);
					REQUIRE(result.get_failure().has_value() == false);
				}
			}
		}
	}
}

SCENARIO("Core Result system should be usable as success by pointer") {
	GIVEN("value variable based on random type") {
		int test_value = 2;
		int* test_ptr = &test_value;
		AND_GIVEN("Success to pass to result") {
			auto const sucess = Success<int*>{test_ptr};
			WHEN("Result is created") {
				auto const result = Result<Success<int*>>(sucess);
				THEN("The result object success should be queried") {
					REQUIRE(result.is_success() == true);
					REQUIRE(result.get_success()->get_value() == test_ptr);
				}
				AND_THEN("The result object failure should not be queriable") {
					REQUIRE(result.is_failure() != true);
					REQUIRE(result.get_failure().has_value() == false);
				}
			}
		}
	}
}

SCENARIO("Core Result system should be usable as failure") {
	GIVEN("Invalid operation") {
		int const* invalid_result = nullptr;
		AND_GIVEN("Failure to pass to result") {
			auto const failure = BasicFailure<Failures::NO_RESOURCES>::create();
			WHEN("Result is created") {
				auto const result = Result<Success<int>, decltype(failure)>(failure);
				THEN("The result object failure should be queried") {
					REQUIRE(result.is_failure() == true);
					REQUIRE(result.get_failure()->get_id() == Failures::NO_RESOURCES);
				}
				AND_THEN("The result object success should not be queriable") {
					REQUIRE(result.is_success() == false);
					REQUIRE(result.get_success().has_value() == false);
				}
			}
		}
	}
}
