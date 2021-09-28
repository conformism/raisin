#include <catch2/catch_all.hpp>

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "domain/cfg/cfg.hpp"

using namespace core::result;
using namespace core;

SCENARIO("Cfg builder should works with uuid") {
	GIVEN("Known UUID") {
		core::Uuid uuid = "randomuuid";
		AND_GIVEN("Exising builder") {
			auto builder = cfg::Cfg::Builder();
			WHEN("Builder take uuid") {
				auto result = builder.set_uuid(uuid);
				THEN("The result shoult not be failure") {
					REQUIRE(result.is_success() == true);
					AND_THEN("The cfg should build") {
						builder = result.get_success()->get_value();
						cfg::Cfg cfg = builder.build();
					}
				}
			}
		}
	}
}

SCENARIO("Cfg builder should works without uuid") {
	GIVEN("Exising builder") {
		auto builder = cfg::Cfg::Builder();
		WHEN("Build") {
			auto const cfg = builder.build();
			THEN("The cfg should build") {}
		}
	}
}

SCENARIO("Cfg builder should fail with invalid uuid") {
	GIVEN("Known UUID") {
		core::Uuid invalid_uuid;
		AND_GIVEN("Exising builder") {
			auto builder = cfg::Cfg::Builder();
			WHEN("Builder take uuid") {
				auto result = builder.set_uuid(invalid_uuid);
				THEN("The result shoult be failure") {
					REQUIRE(result.is_failure() == true);
				}
			}
		}
	}
}

SCENARIO("Cfg builder should works with block") {
	GIVEN("Exising builder") {
		auto builder = cfg::Cfg::Builder();
		AND_GIVEN("Exising block address") {
			auto block_builder = cfg::Block::Builder();
			auto block = block_builder.build();
			auto* block_ptr = &block;
			WHEN("Builder take scope") {
				auto const result = builder.add_block(block_ptr);
				THEN("The result shoult not be failure") {
					REQUIRE(result.is_success() == true);
				}
			}
		}
	}
}

SCENARIO("Cfg builder should works with scope") {
	GIVEN("Exising builder") {
		auto builder = cfg::Cfg::Builder();
		AND_GIVEN("Exising scope address") {
			auto scope_builder = cfg::Scope::Builder();
			auto scope = scope_builder.build();
			auto* scope_ptr = &scope;
			WHEN("Builder take scope") {
				auto const result = builder.add_scope(scope_ptr);
				THEN("The result shoult not be failure") {
					REQUIRE(result.is_success() == true);
				}
			}
		}
	}
}
