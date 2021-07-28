// 120-Bdd-ScenarioGivenWhenThen.cpp

// main() provided in 000-CatchMain.cpp
// #include <catch2/catch.hpp>
#include <any>
#include <catch2/catch_all.hpp>

#include "domain/core/result.hpp"
#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <optional>
#include <string>
#include <vector>

using namespace core::result;

// TEST_CASE("all is good") {
//     REQUIRE(true);
// }

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
				AND_THEN("The result object failure should not be queriable")
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
		AND_GIVEN("Success to pass to result") {
			auto const sucess = Success<int*>{test_ptr};
			WHEN("Result is created") {
				auto const result = Result<Success<int*>>(sucess);
				THEN("The result object success should be queried") {
					REQUIRE(result.is_success() == true);
					REQUIRE(result.get_success()->get_value() == test_ptr);
				}
				AND_THEN("The result object failure should not be queriable")
				REQUIRE(result.is_failure() != true);
				REQUIRE(result.get_failure().has_value() == false);
			}
		}
	}
}
