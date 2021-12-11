if(Catch2_FOUND)
	add_executable( raisin_unittest EXCLUDE_FROM_ALL )

	target_sources( raisin_unittest
		PRIVATE
#		"${CMAKE_CURRENT_SOURCE_DIR}/domain/cfg/test_cfg_builder.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/domain/core/guard.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/domain/core/aggregator.cpp"
	    "${CMAKE_CURRENT_SOURCE_DIR}/domain/program.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/domain/core/compositor.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/infra/repositories/repository-in-memory.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/domain/file/file.cpp"
#        "${CMAKE_CURRENT_SOURCE_DIR}/infra/services/parsers/clang/clang-parser.cpp"
	)

	target_compile_definitions( raisin_unittest
		PRIVATE
		UNITTEST
		$<$<CONFIG:Debug>:DEBUG>
		)

	target_compile_features( raisin_unittest
		PRIVATE
		cxx_std_17
		)

	target_compile_options( raisin_unittest
		PRIVATE
		$<$<CONFIG:Coverage>:-O0>
		$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Wall>
		$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Wextra>
#		$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Weffc++>
		$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-fexceptions>
		)

	target_include_directories( raisin_unittest
		PRIVATE
		"${CMAKE_SOURCE_DIR}/src"
		)

	target_link_libraries( raisin_unittest
		Catch2::Catch2WithMain
		raisin
		)

	file( GLOB_RECURSE RAISIN_UNITTEST_HEADERS "*.hpp" )

	coverage(
		TARGET_TO_RUN raisin_unittest
		TARGETS_TO_COVER raisin
		)

	iwyu(
		TARGET raisin_unittest
		ARGS
			--std=c++17 # Useless with -p ?
#			-p="${CMAKE_BINARY_DIR}" # Outdated iwyu version.
			-Xiwyu
			--no_comments
		)

	clang_format(
		TARGET raisin_unittest
		ADDITIONAL_FILES
			${RAISIN_UNITTEST_HEADERS}
		ARGS
		)

  enable_clang_build_analyzer( TARGET raisin_unittest )

  enable_sanitizers( TARGET raisin_unittest )
endif()
