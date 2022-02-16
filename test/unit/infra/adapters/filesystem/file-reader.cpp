#include <catch2/catch_all.hpp>

#include "infra/adapters/filesystem/file-reader.hpp"

#include <any>
#include <filesystem>
#include <vector>


using namespace infra::adapters::filesystem;
using namespace domain::core::result;
using namespace domain::core;

SCENARIO("File adapter should be able to read file") {
	GIVEN("Exising file_adapter") {
		FileAdapter::Config const config{
			"../test/unit/infra/adapters/filesystem/file-reader.cpp"
		};
		FileAdapter file_adapter{};
		file_adapter.configure(config);

		WHEN("File is read") {
			auto result = file_adapter.read();
			THEN("The result should be ok") {
	            auto failure_value = std::any_cast<std::vector<std::filesystem::path>>(result.get_failure_value().value());
	            for (auto& f: failure_value) {
					INFO("result:" << f);
	            }
				REQUIRE(result.is_success() == true);
			}
		}
	}
}
