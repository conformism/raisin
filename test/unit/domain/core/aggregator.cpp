#include <catch2/catch_all.hpp>

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "domain/core/aggregator.hpp"
#include "domain/core/types.hpp"

using namespace core;

SCENARIO("Core Aggregator should be fillable.") {
	GIVEN("Uuid and related object to insert into it.") {
		Uuid const uuid = "1234567";
		int const value_object = 1234;
		int const* value_object_ptr = &value_object;

		AND_GIVEN("Existing aggregator") {
			auto aggregator = Aggregator<int const>();
			WHEN("Value object is inserted") {
				auto const result = aggregator.insert(uuid, value_object_ptr);
				THEN("The object should be sucessfully inserted.") {
					REQUIRE(result.is_success() == true);
					REQUIRE(result.get_success() == value_object_ptr);
					REQUIRE(aggregator.is_inside(uuid) == true);
					REQUIRE(aggregator.count(uuid) == 1);
				}
				AND_THEN("The value inside the aggregator must be the inserted value.") {
					const int* value_in = aggregator.at(uuid).get_success().value();
					REQUIRE(value_in == value_object_ptr);
				}
			}
		}
	}
}

SCENARIO("Core Aggregator should be removable when object is in.") {
	GIVEN("Uuid and related object inserted into it.") {
		const Uuid uuid = "1234567";
		const int value_object = 1234;
		const int* value_object_ptr = &value_object;
		auto aggregator = Aggregator<int const>();
		auto const result = aggregator.insert(uuid, value_object_ptr);

		WHEN("Value object in is removed.") {
			auto const result = aggregator.remove(uuid);
			THEN("The object should be sucessfully removed.") {
				REQUIRE(result.is_success() == true);
			}
			AND_THEN("The value should not be inside aggregator.") {
				REQUIRE(aggregator.is_inside(uuid) == false);
				REQUIRE(aggregator.count(uuid) == 0);
			}
		}
	}
}

SCENARIO("Core Aggregator should be not removable when object is not in.") {
	GIVEN("Uuid without object not inserted into it.") {
		const Uuid uuid = "1234567";
		auto aggregator = Aggregator<int const>();

		WHEN("Value object in is removed.") {
			auto const result = aggregator.remove(uuid);
			THEN("The result should failure.") {
				REQUIRE(result.is_failure() == true);
			}
			AND_THEN("The value should not be inside aggregator.") {
				REQUIRE(aggregator.is_inside(uuid) == false);
			}
		}
	}
}
