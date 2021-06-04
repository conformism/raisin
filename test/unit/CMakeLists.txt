if( Catch2_FOUND )
	add_executable( unittest EXCLUDE_FROM_ALL )

	target_sources( unittest
		PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/domain/cfg/test_cfg_builder.cpp"
		)

	target_compile_definitions( unittest
		PRIVATE
		UNITTEST
		$<$<CONFIG:Debug>:DEBUG>
		)

	target_compile_features( unittest
		PRIVATE
		cxx_std_17
		)

	target_compile_options( unittest
		PRIVATE
		$<$<CONFIG:Coverage>:-O0>
		$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Wall>
		$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Wextra>
#		$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Weffc++>
		$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-fexceptions>
		)

	target_include_directories( unittest
		PRIVATE
		"${CMAKE_SOURCE_DIR}/src"
		)

	target_link_libraries( unittest
		Catch2::Catch2WithMain
		${PROJECT_NAME}
		)

	set_target_properties( unittest PROPERTIES
		OUTPUT_NAME "unittest"
		)
endif()
