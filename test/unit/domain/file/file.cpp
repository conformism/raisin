#include <catch2/catch_all.hpp>

#include "domain/file/file.hpp"

SCENARIO("File should be usable.") {
	using namespace domain::file;
	GIVEN("Datas about file") {
		auto const *const file_name = "file.txt";
		auto const *const file_name_included = "file2.txt";
		std::filesystem::path path(file_name);
		std::filesystem::path path_included(file_name_included);
		auto language = Language::CPP;

		WHEN("File is created") {
			File file(path, language);
			File file_included(path, language);
			File file_not_included(path, Language::C);
			file.include(&file_included);

			THEN("The object should be usable.") {
				REQUIRE(file.get_path().filename() == file_name);
				REQUIRE(file.get_language() == language);
				REQUIRE(file.get_include(file_included.get_uuid()) .is_success());
				REQUIRE(file.get_include(file_not_included.get_uuid()).is_failure());
			}
		}
	}
}
