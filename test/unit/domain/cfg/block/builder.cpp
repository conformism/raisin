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

SCENARIO("Block builder sould be reusable") {
	GIVEN("Exising builder") {
		auto builder = cfg::Block::Builder();

		WHEN("Build") {
			auto successor = builder.build();
			auto precedent = builder.build();
			auto* successor_ptr = &successor;
			auto* precedent_ptr = &precedent;
			INFO("Precedent" << precedent_ptr);
			INFO("Successor" << successor_ptr);

			THEN("The block should have different address") {
				REQUIRE(successor_ptr != precedent_ptr);
				AND_THEN("The block should have different UUID") {
					INFO("Precedent UUID: " << precedent.get_uuid());
					INFO("Successor UUID: " << successor.get_uuid());

					REQUIRE(precedent.get_uuid() != successor.get_text());
				}
			}
		}
	}
}

SCENARIO("Block builder sould works with multiple actions") {
	GIVEN("Exising builder") {
		auto builder = cfg::Block::Builder();

		AND_GIVEN("Exising blocks address") {
			auto successor = builder.build();
			auto successor_2 = builder.build();
			auto precedent = builder.build();
			auto precedent_2 = builder.build();

			auto* successor_ptr = &successor;
			auto* successor_2_ptr = &successor_2;
			auto* precedent_ptr = &precedent;
			auto* precedent_2_ptr = &precedent_2;

			WHEN("Insert multiple values") {
				auto const successor_result = builder.add_successor(successor_ptr);
				auto const successor_result_2 = builder.add_successor(successor_2_ptr);

				auto const precedent_result = builder.add_precedent(precedent_ptr);
				auto const precedent_result_2 = builder.add_precedent(precedent_2_ptr);

				auto const scope = builder.build();

				THEN("The scope should build") {
					REQUIRE(successor_result.is_success() == true);
					REQUIRE(successor_result_2.is_success() == true);
					REQUIRE(precedent_result.is_success() == true);
					REQUIRE(precedent_result_2.is_success() == true);
				}
			}
		}
	}
}
