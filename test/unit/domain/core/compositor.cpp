#include <catch2/catch_all.hpp>

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "domain/core/compositor.hpp"
#include "domain/core/types.hpp"

using namespace domain::core;

SCENARIO("Core Compositor should be fillable.") {
	GIVEN("Uuid and related object to insert std::stringo it.") {
		Uuid const uuid = "1234567";
		int const value_object = 324413;
		int const* value_object_ptr = &value_object;

		AND_GIVEN("Existing compositor") {
			auto compositor = Compositor<int>();
			WHEN("Value object is inserted") {
				auto const result = compositor.insert(uuid, value_object);
				INFO("value in is: " << *result.get_success());
				THEN("The object should be sucessfully inser*ed.") {
					REQUIRE(result.is_success() == true);
					REQUIRE(compositor.is_inside(uuid) == true);
					REQUIRE(compositor.count(uuid) == 1);
				}
				AND_THEN("The value inside the compositor must be the inserted value.") {
					auto* value_out_ptr = compositor.at(uuid).get_success().value();
					REQUIRE(value_out_ptr != nullptr);
					const int value_out = *value_out_ptr;
					INFO("value in: " << value_out);
					INFO("value out: " << value_object);
					REQUIRE(value_out == value_object);
				}
			}
		}
	}
}

SCENARIO("Core Compositor should be removable when object is in.") {
	GIVEN("Uuid and related object inserted std::stringo it.") {
		const Uuid uuid = "1234567";
		std::string value_object = "String";
		auto compositor = Compositor<std::string>();
		auto const result = compositor.insert(uuid, value_object);

		WHEN("Value object in is removed.") {
			auto const result = compositor.remove(uuid);
			THEN("The object should be sucessfully removed.") {
				REQUIRE(result.is_success() == true);
			}
			AND_THEN("The value should not be inside compositor.") {
				REQUIRE(compositor.is_inside(uuid) == false);
				REQUIRE(compositor.count(uuid) == 0);
			}
		}
	}
}

SCENARIO("Core Compositor should be not removable when object is not in.") {
	GIVEN("Uuid without object not inserted std::stringo it.") {
		const Uuid uuid = "1234567";
		auto compositor = Compositor<std::string const>();

		WHEN("Value object in is removed.") {
			auto const result = compositor.remove(uuid);
			THEN("The result should failure.") {
				REQUIRE(result.is_failure() == true);
			}
			AND_THEN("The value should not be inside compositor.") {
				REQUIRE(compositor.is_inside(uuid) == false);
			}
		}
	}
}
