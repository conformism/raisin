
add_library( ${PROJECT_NAME} STATIC )

target_sources( ${PROJECT_NAME}
	PRIVATE
	"${CMAKE_SOURCE_DIR}/src/domain/cfg/element/element.cpp"
	"${CMAKE_SOURCE_DIR}/src/domain/cfg/block/block.cpp"
	"${CMAKE_SOURCE_DIR}/src/domain/cfg/scope/scope.cpp"
	"${CMAKE_SOURCE_DIR}/src/domain/cfg/cfg.cpp"
	)

target_compile_definitions( ${PROJECT_NAME}
	PRIVATE
#	$<$<CONFIG:Debug>:DEBUG>
#	${LLVM_DEFINITIONS}
#	${CLANG_DEFINITIONS}
	)

target_compile_features( ${PROJECT_NAME}
	PRIVATE
	cxx_std_17
	)

target_compile_options( ${PROJECT_NAME}
	PRIVATE
	$<$<CONFIG:Coverage>:-O0>
	$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Wall>
	$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Wextra>
#	$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Weffc++>
	$<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-fexceptions>
	$<$<AND:$<CONFIG:Coverage>,$<CXX_COMPILER_ID:GNU>>:--coverage>
	$<$<AND:$<CONFIG:Coverage>,$<CXX_COMPILER_ID:Clang>>:-fprofile-instr-generate>
	$<$<AND:$<CONFIG:Coverage>,$<CXX_COMPILER_ID:Clang>>:-fcoverage-mapping>
	)

target_include_directories( ${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
#	${LLVM_INCLUDE_DIRS}
	${CLANG_INCLUDE_DIRS}
	)

target_link_libraries( ${PROJECT_NAME}
	$<$<AND:$<CONFIG:Coverage>,$<CXX_COMPILER_ID:GNU>>:-lgcov>
#	-ldl
#	-ltinfo
#	-lpthread
#	clang
#	clangAST
#	clangAnalysis
#	clangBasic
#	clangDriver
#	clangEdit
#	clangIndex
#	clangFrontend
#	clangFrontendTool
#	clangLex
#	clangParse
#	clangSema
#	clangEdit
#	clangASTMatchers
#	clangRewrite
#	clangRewriteFrontend
#	clangStaticAnalyzerFrontend
#	clangStaticAnalyzerCheckers
#	clangStaticAnalyzerCore
#	clangSerialization
#	clangToolingCore
#	clangTooling
)

target_link_options( ${PROJECT_NAME}
	PRIVATE
	$<$<AND:$<CONFIG:Coverage>,$<CXX_COMPILER_ID:Clang>>:-fprofile-instr-generate>
	)

set_target_properties( ${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "raisin"
	)
