#include <catch2/catch_all.hpp>
#include <memory>

#include "domain/cfg/cfg.hpp"
#include "domain/cfg/icfg.hpp"
#include "domain/core/aggregator.hpp"
#include "domain/core/types.hpp"
#include "domain/irepository.hpp"
#include "infra/repositories/repository-in-memory.hpp"
#include "infra/services/cfg/cfg-parser-clang.hpp"
#include "infra/services/cfg/icfg-parser.hpp"

#include "cfg-parser-mock.hpp"

using namespace domain::core::result;
using namespace domain::core;

SCENARIO("Cfg repository save should works with valid Cfgs") {
	GIVEN("Exising CfgParserService") {
		using CfgParserService = infra::services::cfg::CfgParserMock;
		auto cfg_parser_service = std::make_unique<CfgParserService>(CfgParserService());
		cfg_parser_service->mock();

		AND_GIVEN("Exising repository in memory") {
			using Repo = infra::repository::RespositoryInMemory<domain::cfg::Cfg, CfgParserService>;

			std::unique_ptr<domain::IRespository<domain::cfg::Cfg>> repo =
				std::make_unique<Repo>(Repo(std::move(cfg_parser_service)));
			WHEN("Respository save CFG") {
				auto builder = domain::cfg::Cfg::Builder();
				auto scope_builder = domain::cfg::Scope::Builder();
				auto scope = scope_builder.build();
				auto* scope_ptr = &scope;
				auto const add_scope_result = builder.add_scope(scope_ptr);
				if (add_scope_result.is_success()) {
					domain::cfg::Cfg cfg = builder.build();
					const auto cfgs = domain::IRespository<domain::cfg::Cfg>::Cfgs();
					repo->save_cfgs(cfgs);
					THEN("TODO") {
						AND_WHEN("The repository read cfg.") {
							THEN("TODO") {}
						}
					}
				} else {
					REQUIRE(false);
				}
			}
		}
	}
}
