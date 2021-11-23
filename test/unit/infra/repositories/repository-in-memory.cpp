#include <catch2/catch_all.hpp>
#include <memory>

#include "domain/cfg/cfg.hpp"
#include "domain/cfg/icfg.hpp"
#include "domain/core/aggregator.hpp"
#include "domain/core/types.hpp"
#include "domain/irepository.hpp"
#include "infra/repositories/repository-in-memory.hpp"

using namespace domain::core::result;
using namespace domain::core;

SCENARIO("Cfg repository read should return program") {
	GIVEN("Exising repository in memory into unique_ptr") {
		using Repo = infra::repository::RespositoryInMemory;
		std::unique_ptr<Repo> repo = std::make_unique<Repo>(Repo());

		WHEN("Respository read program") {
			THEN("The program should be returned") {
				REQUIRE(repo->read() != nullptr);
			}
		}
	}
}

SCENARIO("Cfg repository write should works") {
	GIVEN("Exising repository in memory into unique_ptr") {
		using Repo = infra::repository::RespositoryInMemory;
		std::unique_ptr<Repo> repo = std::make_unique<Repo>(Repo());
		auto program = domain::Program();
		auto builder = domain::cfg::Cfg::Builder();
		domain::cfg::Cfg cfg_1 = builder.build();
		auto result = program.insert_cfg(cfg_1);

		WHEN("Respository write program") {
			repo->write(std::move(program));
			THEN("The program should be inside repo") {
				REQUIRE(repo->read()->get_cfg_by_uuid(cfg_1.get_uuid()).is_success());
			}
		}
	}
}
