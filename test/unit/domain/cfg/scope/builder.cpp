#include "domain/core/types.hpp"
#include <catch2/catch_all.hpp>

#include "domain/cfg/scope/scope.hpp"
#include "domain/core/result.hpp"

#include <any>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <optional>
#include <string>
#include <vector>

using namespace core::result;

SCENARIO("Scope builder should works with uuid") {
	GIVEN("Known UUID") {
		core::Uuid uuid = "randomuuid";
		AND_GIVEN("Exising builder") {
			auto builder = cfg::Scope::Builder();
			WHEN("Builder take uuid") {
				auto result = builder.set_uuid(uuid);
				THEN("The result shoult not be failure") {
					REQUIRE(result.is_success() == true);
					AND_THEN("The scope sould build.") {
						builder = result.get_success()->get_value();
						cfg::Scope scope = builder.build();
					}
				}
			}
		}
	}
}

SCENARIO("Scope builder should fail with invalid uuid") {
	GIVEN("Known UUID") {
		core::Uuid invalid_uuid;
		AND_GIVEN("Exising builder") {
			auto builder = cfg::Scope::Builder();
			WHEN("Builder take uuid") {
				auto result = builder.set_uuid(invalid_uuid);
				THEN("The result shoult be failure") {
					REQUIRE(result.is_failure() == true);
				}
			}
		}
	}
}

SCENARIO("Scope builder should works with parent") {
	GIVEN("Exising builder") {
		auto builder = cfg::Scope::Builder();
		AND_GIVEN("Exising scope address") {
			auto scope = builder.build();
			cfg::Scope* scope_ptr = &scope;
			WHEN("Builder take scope") {
				auto const result = builder.set_parent(scope_ptr);
				THEN("The result shoult not be failure") {
					REQUIRE(result.is_success() == true);
				}
			}
		}
	}
}

SCENARIO("Scope builder should works with block") {
	GIVEN("Known Block address") {
		cfg::Block::Builder block_builder = cfg::Block::Builder();
		block_builder.set_uuid("12212121");
		cfg::Block block = block_builder.build();
		auto* block_ptr = &block;
		AND_GIVEN("Exising builder") {
			auto builder = cfg::Scope::Builder();
			WHEN("Builder take block") {
				auto result = builder.add_block(&block);
				//     THEN("The result shoult be a success") {
				//         REQUIRE(result.is_success() == true);
				//     }
			}
		}
	}
}
