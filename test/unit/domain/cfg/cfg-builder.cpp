#include <catch2/catch_all.hpp>

#include "domain/cfg/cfg.hpp"

using namespace cfg;

SCENARIO("Create cfg using his builder class") {
	GIVEN("A Cfg builder") {
		auto const builder = Cfg::Builder();
		WHEN("Cfg is builded") {
			THEN("The result object success should be queried") {}
			AND_THEN("The result object failure should not be queriable") {}
		}
	}
}
