#include <catch2/catch_all.hpp>

#include "domain/file/file.hpp"

SCENARIO("File should be usable.") {
	using namespace domain::file;
	GIVEN("Datas about file") {
		auto file_name = "file.txt";
		std::filesystem::path path(file_name);
		auto language = Language::CPP;

		WHEN("File is created") {
			File const file(path, language);
			THEN("The object should be usable.") {
				REQUIRE(file.get_path().filename() == file_name);
				REQUIRE(file.get_language() == language);
			}
		}
	}
}
