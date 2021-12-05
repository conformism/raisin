#include <catch2/catch_all.hpp>

#include <any>
#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
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
				REQUIRE(result.get_success().value() == test_value);
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

SCENARIO("Core Result helper should be usable as failure with one possibility") {
	GIVEN("Invalid operation") {
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

SCENARIO("Core Result helper should be usable as failure with some possibility") {
	GIVEN("Invalid operation") {
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

SCENARIO("Core Result failure appening should works") {
	GIVEN("Invalid operation result") {
		auto const result_test = failure<int, Failures::INVALID_UUID>();
		WHEN("Result combine") {
			Result<int, Failures::NOT_INSIDE, Failures::INVALID_UUID> const combined_result =
				result_test.append_failures<Failures::NOT_INSIDE>();

			THEN("The setted result object should be queried") {
				REQUIRE(combined_result.is_failure() == true);
				REQUIRE(combined_result.get_failure() == Failures::INVALID_UUID);
			}
		}
	}
}

SCENARIO("Core Result success setting should works") {
	GIVEN("Invalid operation result") {
		auto const result_test = failure<int, Failures::INVALID_UUID>();
		WHEN("Result combine") {
			Result<int, Failures::NOT_INSIDE, Failures::INVALID_UUID> const combined_result =
				result_test.append_failures<Failures::NOT_INSIDE>();

			THEN("The setted result object should be queried") {
				REQUIRE(combined_result.is_failure() == true);
				REQUIRE(combined_result.get_failure() == Failures::INVALID_UUID);
			}
		}
	}
}

SCENARIO("core result failure removing should works with one failure id") {
	GIVEN("invalid operation result") {
		auto const result_test = failure<
			int,
			Failures::INVALID_UUID,
			Failures::INVALID_UUID,
			Failures::NOT_INSIDE,
			Failures::NO_RESOURCES,
			Failures::UNKNOWN>();
		WHEN("result removing") {
			auto const new_result = result_test.set_failures<Failures::INVALID_UUID>();

			THEN("the combined result object should be coherent") {
				INFO("result_test type is:" << typeid(result_test).name());
				INFO("new_result tested type is :" << typeid(new_result.value()).name());
				INFO(
					"new_result correct type is:"
					<< typeid(Result<int, Failures::INVALID_UUID>).name());
				REQUIRE(new_result.has_value() == true);
				REQUIRE(new_result.value().get_failure().value() == Failures::INVALID_UUID);
				REQUIRE(
					typeid(decltype(new_result.value())).name()
					== typeid(Result<int, Failures::INVALID_UUID>).name());
			}
		}
	}
}

SCENARIO("Core Result failure removing should works with many failures Ids") {
	GIVEN("Invalid operation result") {
		auto const result_test = failure<
			int,
			Failures::INVALID_UUID,
			Failures::INVALID_UUID,
			Failures::NOT_INSIDE,
			Failures::NO_RESOURCES,
			Failures::UNKNOWN>();
		WHEN("Result setting") {
			auto const new_result = result_test.set_failures<
				Failures::INVALID_UUID,
				Failures::NO_RESOURCES,
				Failures::NOT_INSIDE>();

			THEN("The setted result object should be coherent") {
				// INFO("result_test Failure Id is: " << result_test.get_failure().value());
				INFO("result_test type is:" << typeid(result_test).name());
				INFO("new_result tested type is :" << typeid(new_result.value()).name());
				INFO(
					"new_result correct type is:" << typeid(Result<
																int,
																Failures::INVALID_UUID,
																Failures::NO_RESOURCES,
																Failures::NOT_INSIDE>)
														 .name());
				REQUIRE(new_result.has_value() == true);
				REQUIRE(new_result.value().get_failure().value() == Failures::INVALID_UUID);
				REQUIRE(
					typeid(decltype(new_result.value())).name()
					== typeid(Result<
								  int,
								  Failures::INVALID_UUID,
								  Failures::NO_RESOURCES,
								  Failures::NOT_INSIDE>)
						   .name());
			}
		}
	}
}

SCENARIO("Core Result failure removing should works with success") {
	GIVEN("Valid operation result") {
		constexpr int success_value = 2;
		auto const result_test = success<
			int,
			Failures::INVALID_UUID,
			Failures::NOT_INSIDE,
			Failures::NO_RESOURCES,
			Failures::UNKNOWN>(success_value);
		WHEN("Result setting") {
			auto const new_result = result_test.set_failures<
				Failures::INVALID_UUID,
				Failures::NO_RESOURCES,
				Failures::NOT_INSIDE>();

			THEN("The setted result object should be coherent") {
				// INFO("result_test Failure Id is: " << result_test.get_failure().value());
				INFO("result_test type is:" << typeid(result_test).name());
				INFO("new_result tested type is :" << typeid(new_result.value()).name());
				INFO(
					"new_result correct type is:" << typeid(Result<
																int,
																Failures::INVALID_UUID,
																Failures::NO_RESOURCES,
																Failures::NOT_INSIDE>)
														 .name());
				REQUIRE(new_result.has_value() == true);
				REQUIRE(new_result.value().get_success().value() == success_value);
				REQUIRE(
					typeid(decltype(new_result.value())).name()
					== typeid(Result<
								  int,
								  Failures::INVALID_UUID,
								  Failures::NO_RESOURCES,
								  Failures::NOT_INSIDE>)
						   .name());
			}
		}
	}
}

SCENARIO(
	"Core Result failure setting should fail if not at least one setted is equal to the base "
	"Result value") {
	GIVEN("Invalid operation result") {
		auto const result_test = failure<
			int,
			Failures::INVALID_UUID,
			Failures::INVALID_UUID,
			Failures::NOT_INSIDE,
			Failures::NO_RESOURCES,
			Failures::UNKNOWN>();
		WHEN("Result setting") {
			auto const new_result = result_test.set_failures<Failures::NOT_INSIDE>();

			THEN("The setted result object should be coherent") {
				INFO("result_test type is:" << typeid(result_test).name());
				INFO("new_result tested type is :" << typeid(new_result.value()).name());
				REQUIRE(new_result.has_value() == false);
			}
		}
	}
}
// TODO(Add tests for success setting with failure)
SCENARIO("Core Result success setting should works with failure") {
	GIVEN("Invalid operation result") {
		auto const result_test = failure<
			int,
			Failures::INVALID_UUID,
			Failures::INVALID_UUID,
			Failures::NOT_INSIDE,
			Failures::NO_RESOURCES,
			Failures::UNKNOWN>();
		WHEN("Result setting") {
			auto const new_result = result_test.set_success<std::string>();

			THEN("The setted result object should be coherent") {
				INFO("result_test type is:" << typeid(result_test).name());
				INFO("new_result tested type is :" << typeid(new_result.value()).name());
				REQUIRE(new_result.has_value() == true);
				REQUIRE(new_result.value().is_failure() == true);
				REQUIRE(new_result.value().get_failure().value() == Failures::INVALID_UUID);
			}
		}
	}
}

SCENARIO("core result success setting should works with success") {
	GIVEN("valid operation result") {
		constexpr int success_value = 2;
		auto const result_test =
			success<int, Failures::INVALID_UUID, Failures::NOT_INSIDE>(success_value);
		WHEN("result setting") {
			const float new_success_value = 2.3;
			Result<float, Failures::INVALID_UUID, Failures::NOT_INSIDE> const new_result =
				result_test.set_success<float>(new_success_value);

			THEN("the setted result object should be coherent") {
				INFO("result_test type is:" << typeid(result_test).name());
				INFO("new_result tested type is :" << typeid(new_result).name());
				REQUIRE(new_result.is_success() == true);
				REQUIRE(new_result.get_success().value() == new_success_value);
			}
		}
	}
}
