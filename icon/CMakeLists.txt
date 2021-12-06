find_program( PDF2SVG NAMES pdf2svg )
if( PDF2SVG )
	message( STATUS "Found pdf2svg: ${PDF2SVG}" )
else()
	message( ERROR "Not found pdf2svg: install it" )
endif()

include( Latex )

compile_latex_file( "icon"
	OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/icon.svg"
	TEXINPUTS "${CMAKE_CURRENT_SOURCE_DIR}"
	REGISTER_TO "ICON_FILES"
	SHELL_ESCAPE
	)

add_custom_target( icon
	DEPENDS ${ICON_FILES}
	COMMAND ${CMAKE_COMMAND} -E copy
		"${CMAKE_CURRENT_BINARY_DIR}/icon.svg"
		"${CMAKE_SOURCE_DIR}/icon/raisin.svg"
	COMMENT "Copying icon.svg back to ${CMAKE_SOURCE_DIR}/icon/raisin.svg"
	)
