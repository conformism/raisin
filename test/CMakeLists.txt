
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/unit" )

include( CTest )

add_custom_target( check
	VERBATIM
	USES_TERMINAL
	COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
	COMMENT "Running tests"
	DEPENDS raisin_unittest
	)

add_test( NAME RaisinUnittest
	COMMAND $<TARGET_FILE:raisin_unittest> --use-colour=yes
	)
