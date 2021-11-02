#include <catch2/catch_all.hpp>

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "domain/core/result.hpp"

using namespace domain::core::result;

SCENARIO("Core Result system should be usable as success by value") {
	GIVEN("value variable based on random type") {
		int test_value = 2;
		WHEN("Result is created") {
			auto const result = Result<int>::create(test_value);
			THEN("The result object success should be queried") {
				REQUIRE(result.is_success() == true);
				REQUIRE(result.get_success() == test_value);
			}
			AND_THEN("The result object failure should not be queriable") {
				REQUIRE(result.is_failure() != true);
				REQUIRE(result.get_failure().has_value() == false);
			}
		}
	}
}

SCENARIO("Core Result system should be usable as success by pointer") {
	GIVEN("value variable based on random type") {
		int test_value = 2;
		int* test_ptr = &test_value;
		WHEN("Result is created") {
			auto const result = Result<int*>::create(test_ptr);
			THEN("The result object success should be queried") {
				REQUIRE(result.is_success() == true);
				REQUIRE(result.get_success().value() == test_ptr);
			}
			AND_THEN("The result object failure should not be queriable") {
				REQUIRE(result.is_failure() != true);
				REQUIRE(result.get_failure().has_value() == false);
			}
		}
	}
}

SCENARIO("Core Result system should be usable as failure") {
	GIVEN("Invalid operation") {
		int const* invalid_result = nullptr;
		WHEN("Result is created") {
			auto const result =
				Result<int, Failures::NO_RESOURCES>::create<Failures::NO_RESOURCES>();
			THEN("The result object failure should be queried") {
				REQUIRE(result.is_failure() == true);
				REQUIRE(result.get_failure() == Failures::NO_RESOURCES);
			}
			AND_THEN("The result object success should not be queriable") {
				REQUIRE(result.is_success() == false);
				REQUIRE(result.get_success().has_value() == false);
			}
		}
	}
}

SCENARIO("Core Result helper should be usable as success by value") {
	GIVEN("value variable based on random type") {
		int test_value = 2;
		WHEN("Result is created") {
			auto const result = success<int>(test_value);
			THEN("The result object success should be queried") {
				REQUIRE(result.is_success() == true);
				REQUIRE(result.get_success() == test_value);
			}
			AND_THEN("The result object failure should not be queriable") {
				REQUIRE(result.is_failure() != true);
				REQUIRE(result.get_failure().has_value() == false);
			}
		}
	}
}

SCENARIO("Core Result helper should be usable as failure with one possibility.") {
	GIVEN("Invalid operation") {
		int const* invalid_result = nullptr;
		WHEN("Result is created") {
			auto const result = failure<int, Failures::NO_RESOURCES>();
			THEN("The result object failure should be queried") {
				REQUIRE(result.is_failure() == true);
				REQUIRE(result.get_failure() == Failures::NO_RESOURCES);
			}
			AND_THEN("The result object success should not be queriable") {
				REQUIRE(result.is_success() == false);
				REQUIRE(result.get_success().has_value() == false);
			}
		}
	}
}

SCENARIO("Core Result helper should be usable as failure with some possibility.") {
	GIVEN("Invalid operation") {
		int const* invalid_result = nullptr;
		WHEN("Result is created") {
			auto const result = failure<
				int,
				Failures::NO_RESOURCES,
				Failures::NO_RESOURCES,
				Failures::INVALID_UUID>();
			THEN("The result object failure should be queried") {
				REQUIRE(result.is_failure() == true);
				REQUIRE(result.get_failure() == Failures::NO_RESOURCES);
			}
			AND_THEN("The result object success should not be queriable") {
				REQUIRE(result.is_success() == false);
				REQUIRE(result.get_success().has_value() == false);
			}
		}
	}
}

SCENARIO("Core Result combine should works.") {
	GIVEN("Invalid operation result") {
		auto const result_test = failure<int, Failures::INVALID_UUID>();
		WHEN("Result combine") {
			Result<int, Failures::NOT_INSIDE, Failures::INVALID_UUID> const combined_result =
				result_test.append<int, Failures::NOT_INSIDE>();

			THEN("The combined result object should be queried") {
				REQUIRE(combined_result.is_failure() == true);
				REQUIRE(combined_result.get_failure() == Failures::INVALID_UUID);
			}
		}
	}
}
