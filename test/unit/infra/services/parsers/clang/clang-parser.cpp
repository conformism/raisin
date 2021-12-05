#include <catch2/catch_all.hpp>
#include <memory>

#include "infra/services/parsers/clang/clang-paser.hpp"

using namespace domain::core::result;
using namespace domain::core;

// SCENARIO("Cfg repository read should return program") {
//     GIVEN("Exising repository in memory into unique_ptr") {
//         using Repo = infra::repository::RespositoryInMemory;
//         std::unique_ptr<Repo> repo = std::make_unique<Repo>(Repo());

//         WHEN("Respository read program") {
//             THEN("The program should be returned") {
//                 REQUIRE(repo->read() != nullptr);
//             }
//         }
//     }
// }
