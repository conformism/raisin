#include <catch2/catch_all.hpp>

#include "domain/file/file.hpp"
#include "domain/file/code.hpp"

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

			WHEN("Code is created") {
				constexpr auto start_line = 0;
				constexpr auto end_line = 20000;
				constexpr auto start_char = 0;
				constexpr auto end_char = 50000;

				Code const code = Code(file.get_uuid(), start_line, end_line, start_char, end_char);
				Code const same_code = Code(file.get_uuid(), start_line, end_line, start_char, end_char);
				Code const different_code = Code(file.get_uuid(), start_line, end_line, 0, 17);

				THEN("The code object be usable and comparable") {
					REQUIRE(code == same_code);
					REQUIRE(code != different_code);

					REQUIRE(code.get_start_line() == start_line);
					REQUIRE(code.get_end_line() == end_line);
					REQUIRE(code.get_start_char() == start_char);
					REQUIRE(code.get_end_char() == end_char);
				}
			}
		}
	}
}
