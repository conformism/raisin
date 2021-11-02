#include <catch2/catch_all.hpp>

#include "domain/cfg/scope/scope.hpp"

using namespace domain::cfg;

SCENARIO("Create scopes without blocks to test scope creation") {
	GIVEN("A root scope") {
		auto const root_scope = Scope();
		WHEN("Cfg is builded") {
			THEN("The result object success should be queried") {}
			AND_THEN("The result object failure should not be queriable") {}
		}
	}
}
