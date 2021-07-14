// 120-Bdd-ScenarioGivenWhenThen.cpp

// main() provided in 000-CatchMain.cpp
// #include <catch2/catch.hpp>
#include <any>
#include <catch2/catch_all.hpp>

#include "domain/core/result.hpp"
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <optional>
#include <string>
#include <vector>

using namespace core::result;

static std::string const invalid_name = "Invalid use case for tests";
static std::string const invalid_reason = "Just for tests";
TEST_CASE("all is good") {
    REQUIRE(true);
}

class Invalid : public InvalidUseCaseTypes {
public:
    [[nodiscard]] auto get_name() const -> std::string override {
        return invalid_name;
    };
    [[nodiscard]] auto get_reason() const -> std::string override {
        return invalid_reason;
    };
};

SCENARIO("Core Result system should be extensible and instanciable") {
    GIVEN("Minimal invalid use case type extension") {
        Invalid const invalid = Invalid();
        WHEN("Invalid use case methods are used")
        THEN("They must return correct reason why a failure happen") {
            REQUIRE(invalid.get_name() == invalid_name);
            REQUIRE(invalid.get_reason() == invalid_reason);
        }
    }
}

SCENARIO("Basic domain value result should be declarable as success") {
    GIVEN("Factory create value result") {
        auto const resultFactory = Factory<int, Invalid>();
        AND_GIVEN("Random int value to return as result") {
            int const value = 12;
            // Validate assumption of the GIVEN clause
            THEN("The result factory should return valid result") {
                auto const result = Factory<int, Invalid>::create(value);

                WHEN("Result type is asked") {
                    THEN("The result should return that is a success") {
                        REQUIRE(result.is_success() == true);
                    }
                }
                WHEN("Result value is requested") {
                    THEN("The result value should be equal to given factory value") {
                        REQUIRE(result.get_value() == value);
                    }
                }
                WHEN("Result error is requested") {
                    THEN("The result error value should be empty") {
                        REQUIRE(result.get_error() == std::nullopt);
                    }
                }
            }
        }
    }
}

SCENARIO("Basic domain value result should be declarable as failure") {
    GIVEN("Factory create value result") {
        auto const resultFactory = Factory<int, Invalid>();
        AND_GIVEN("Invalid use case object") {
            Invalid failure = Invalid();
            // Validate assumption of the GIVEN clause
            THEN("The result factory should return valid result") {
                auto const result = Factory<int, Invalid>::create(failure);

                WHEN("Result type is asked") {
                    THEN("The result should return that is a failure") {
                        REQUIRE(result.is_success() == false);
                    }
                }
                WHEN("Result value is requested") {
                    THEN("The result value should be empty") {
                        REQUIRE(result.get_value() == std::nullopt);
                    }
                }
            }
        }
    }
}
