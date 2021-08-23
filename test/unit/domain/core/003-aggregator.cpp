#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "domain/core/aggregator.hpp"
#include "domain/core/types.hpp"

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

using namespace core;

SCENARIO("Core Aggregator should be fillable.") {
	GIVEN("Uuid and related object to insert into it.") {
		const Uuid uuid = "1234567";
		const int value_object = 1234;
		const int* value_object_ptr = &value_object;

		AND_GIVEN("Existing aggregator") {
			auto aggregator = Aggregator<int const>();
			WHEN("Value object is inserted") {
				auto const result = aggregator.insert_or_assign(uuid, value_object_ptr);
				THEN("The object should be sucessfully inserted.") {
					REQUIRE(result.is_success() == true);
					REQUIRE(result.get_success()->get_value() == value_object_ptr);
					REQUIRE(aggregator.is_inside(uuid) == true);
				}
				AND_THEN("The value inside the aggregator must be the ineserted value.") {
					const int* value_in = aggregator.at(uuid).get_success()->get_value();
					REQUIRE(value_in == value_object_ptr);
				}
			}
		}
	}
}
