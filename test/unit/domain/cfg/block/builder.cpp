#include <catch2/catch_all.hpp>

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "domain/cfg/scope/scope.hpp"
using namespace core::result;
using namespace core;

SCENARIO("Block builder should works with uuid") {
	GIVEN("Known UUID") {
		core::Uuid uuid = "randomuuid";
		AND_GIVEN("Exising builder") {
			auto builder = cfg::Block::Builder();
			WHEN("Builder take uuid") {
				auto result = builder.set_uuid(uuid);
				THEN("The result shoult not be failure") {
					REQUIRE(result.is_success() == true);
					AND_THEN("The scope sould build") {
						auto* const builder = result.get_success().value();
						cfg::Block scope = builder->build();
					}
				}
			}
		}
	}
}

SCENARIO("Block builder should works without uuid") {
	GIVEN("Exising builder") {
		auto builder = cfg::Block::Builder();
		WHEN("Build") {
			auto const scope = builder.build();
			THEN("The scope should build") {}
		}
	}
}

SCENARIO("Block builder should fail with invalid uuid") {
	GIVEN("Known UUID") {
		core::Uuid invalid_uuid;
		AND_GIVEN("Exising builder") {
			auto builder = cfg::Block::Builder();
			WHEN("Builder take uuid") {
				auto result = builder.set_uuid(invalid_uuid);
				THEN("The result shoult be failure") {
					REQUIRE(result.is_failure() == true);
				}
			}
		}
	}
}

SCENARIO("Block builder should works with precedent") {
	GIVEN("Exising builder") {
		auto builder = cfg::Block::Builder();
		AND_GIVEN("Exising blocks address") {
			auto precedent = builder.build();
			auto* precedent_ptr = &precedent;
			WHEN("Builder take scope") {
				auto const result = builder.add_precedent(precedent_ptr);
				THEN("The result shoult not be failure") {
					REQUIRE(result.is_success() == true);
				}
			}
		}
	}
}

SCENARIO("Block builder should works with successor") {
	GIVEN("Exising builder") {
		auto builder = cfg::Block::Builder();
		AND_GIVEN("Exising blocks address") {
			auto successor = builder.build();
			auto* successor_ptr = &successor;
			WHEN("Builder take scope") {
				auto const result = builder.add_precedent(successor_ptr);
				THEN("The result shoult not be failure") {
					REQUIRE(result.is_success() == true);
				}
			}
		}
	}
}

SCENARIO("Block builder sould be chained") {
	GIVEN("Exising builder") {
		auto builder = cfg::Block::Builder();

		AND_GIVEN("Exising blocks address") {
			auto successor = builder.build();
			auto precedent = builder.build();
			auto* successor_ptr = &successor;
			auto* precedent_ptr = &precedent;
			WHEN("Chain") {
				INFO("precedent ptr" << successor_ptr);
				INFO("precedent ptr" << precedent_ptr);
				auto const successor_result = builder.add_successor(successor_ptr);
				auto const precedent_result = builder.add_successor(precedent_ptr);
				auto f = precedent_result.get_failure().value();
				auto const scope = builder.build();

				THEN("The scope should build") {
					REQUIRE(successor_result.is_success() == true);
					// REQUIRE(f == Failures::NO_RESOURCES);
					REQUIRE(precedent_result.is_success() == true);
				}
			}
		}
	}
}
