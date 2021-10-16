#include <catch2/catch_all.hpp>

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "domain/cfg/scope/scope.hpp"

using namespace core::result;
using namespace core;

SCENARIO("Scope builder should works with uuid") {
	GIVEN("Known UUID") {
		core::Uuid uuid = "randomuuid";
		AND_GIVEN("Exising builder") {
			auto builder = cfg::Scope::Builder();
			WHEN("Builder take uuid") {
				auto result = builder.set_uuid(uuid);
				THEN("The result shoult not be failure") {
					REQUIRE(result.is_success() == true);
					AND_THEN("The scope sould build") {
						builder = result.get_success()->get_value();
						cfg::Scope scope = builder.build();
					}
				}
			}
		}
	}
}

SCENARIO("Scope builder should works without uuid") {
	GIVEN("Exising builder") {
		auto builder = cfg::Scope::Builder();
		WHEN("Build") {
			auto const scope = builder.build();
			THEN("The scope should build") {}
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
		core::Uuid const uuid = "1234567";
		block_builder.set_uuid(uuid);
		cfg::Block block = block_builder.build();
		auto* block_ptr = &block;
		AND_GIVEN("Exising builder") {
			auto builder = cfg::Scope::Builder();
			WHEN("Builder take block") {
				auto result = builder.add_block(block_ptr);
				THEN("The result shoult be a success") {
					REQUIRE(result.is_success() == true);
					AND_THEN("The scope should build") {
						auto const scope = builder.build();
					}
				}
			}
		}
	}
}

SCENARIO("Scope builder sould be reusable") {
	GIVEN("Exising builder") {
		auto builder = cfg::Scope::Builder();

		WHEN("Build") {
			auto successor = builder.build();
			auto precedent = builder.build();
			auto* successor_ptr = &successor;
			auto* precedent_ptr = &precedent;
			INFO("Precedent" << precedent_ptr);
			INFO("Successor" << successor_ptr);

			THEN("The scope should have different address") {
				REQUIRE(successor_ptr != precedent_ptr);
				AND_THEN("The scope should have different UUID") {
					INFO("Precedent UUID: " << precedent.get_uuid());
					INFO("Successor UUID: " << successor.get_uuid());

					REQUIRE(precedent.get_uuid() != successor.get_uuid());
				}
			}
		}
	}
}

SCENARIO("Scope builder sould works with multiple actions") {
	GIVEN("Exising builders") {
		auto builder = cfg::Scope::Builder();
		auto block_builder = cfg::Block::Builder();

		AND_GIVEN("Exising scopes address") {
			auto parent = builder.build();
			auto child = builder.build();
			auto child_2 = builder.build();
			auto block = block_builder.build();
			auto block_2 = block_builder.build();

			auto* parent_ptr = &parent;
			auto* child_ptr = &child;
			auto* child_2_ptr = &child_2;
			auto* block_ptr = &block;
			auto* block_2_ptr = &block_2;

			WHEN("Insert multiple values") {
				auto const child_result = builder.add_child(child_ptr);
				auto const child_result_2 = builder.add_child(child_2_ptr);
				auto const parent_result = builder.set_parent(parent_ptr);
				auto const block_result = builder.add_block(block_ptr);
				auto const block_result_2 = builder.add_block(block_2_ptr);

				auto const scope = builder.build();

				THEN("The scope should build") {
					REQUIRE(child_result.is_success() == true);
					REQUIRE(child_result_2.is_success() == true);
					REQUIRE(parent_result.is_success() == true);
					REQUIRE(block_result.is_success() == true);
					REQUIRE(block_result_2.is_success() == true);
				}
			}
		}
	}
}
