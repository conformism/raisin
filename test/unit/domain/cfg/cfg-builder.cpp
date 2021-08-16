#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "domain/cfg/cfg.hpp"

using namespace cfg;

SCENARIO("Create cfg using his builder class") {
	GIVEN("A Cfg builder") {
		auto const builder = Cfg::Builder();
		WHEN("Cfg is builded") {
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
