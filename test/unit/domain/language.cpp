#include <catch2/catch_all.hpp>

#include "domain/language.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace domain::language;

SCENARIO("Language should be usable") {
	GIVEN("Language") {
		using TestC = SupportedLanguage<Name::C, Paradigm::FUNCTIONAL, Paradigm::OBJECT, Paradigm::META>;
		using TestCpp = SupportedLanguage<Name::CPP>;

		TestC test_c = TestC();
		TestCpp test_cpp = TestCpp();
		Cpp cpp = Cpp();

		WHEN("Languages paradigm is compared") {
			THEN("It should be ok") {
				REQUIRE(test_c.has_paradigm(Paradigm::FUNCTIONAL));
			}
		}
		WHEN("Languages names are compared") {
			THEN("The languages names should correspond") {}
			REQUIRE(cpp.get_name() != test_c.get_name());
			REQUIRE(cpp.get_name() == test_cpp.get_name());
		}
		WHEN("The languages is casted as generic language") {
			Language const* generic_test_c = &test_c;
			Language const* generic_test_cpp = &test_cpp;
			Language const* generic_cpp = &cpp;

			THEN("It should works as supported language") {
				REQUIRE(test_c.has_paradigm(Paradigm::FUNCTIONAL));
				REQUIRE(*generic_cpp != *generic_test_c);
				REQUIRE(*generic_test_cpp == *generic_cpp);
				REQUIRE(cpp.has_paradigm(Paradigm::FUNCTIONAL));
			}
		}
	}
}
