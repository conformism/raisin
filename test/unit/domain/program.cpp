#include <catch2/catch_all.hpp>

#include <any>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "domain/program.hpp"

using namespace domain::core::result;
using namespace domain::core;

SCENARIO("Program should works with UUID") {
	GIVEN("Program ") {
		domain::Program program = domain::Program();
		AND_GIVEN("Exising cfg") {
			auto const cfg = domain::cfg::Cfg();
			WHEN("The cfg is inserted into program") {
				auto const uuid = cfg.get_uuid();
				auto result = program.insert_cfg(cfg);
				THEN("The result sould be success with good value") {
					REQUIRE(result.is_success());
					REQUIRE(cfg.get_uuid() == result.get_success().value()->get_uuid());
					AND_WHEN("The cfg is queries from program") {
						auto result = program.get_cfg_by_uuid(uuid);
						THEN("The result should be successed with good value") {
							REQUIRE(result.is_success());
							REQUIRE(result.get_success().value()->get_uuid() == uuid);
						}
					}
					AND_WHEN("The cfg is remove from program") {
						auto result = program.remove_cfg(uuid);
						THEN("The result should be successed") {
							REQUIRE(result.is_success());
						}
					}
				}
			}
		}
	}
}
