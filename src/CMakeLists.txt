add_library(raisin SHARED)

target_sources(
  raisin
  PRIVATE "${CMAKE_SOURCE_DIR}/src/domain/core/types.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/core/guard.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/cfg/element/element.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/cfg/block/block.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/cfg/block/builder.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/cfg/scope/scope.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/cfg/scope/builder.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/cfg/cfg.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/cfg/cfg.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/cfg/builder.cpp"
          "${CMAKE_SOURCE_DIR}/src/domain/program.cpp")

target_compile_definitions(
  raisin PRIVATE # $<$<CONFIG:Debug>:DEBUG> ${LLVM_DEFINITIONS}
                 # ${CLANG_DEFINITIONS}
)

target_compile_features(raisin PRIVATE cxx_std_17)

target_compile_options(
  raisin
  PRIVATE $<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Wall>
          $<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Wextra>
          # $<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-Weffc++>
          $<$<OR:$<CONFIG:Coverage>,$<CONFIG:Debug>>:-fexceptions>)

target_include_directories(
  raisin
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          # ${LLVM_INCLUDE_DIRS}
          ${CLANG_INCLUDE_DIRS})

# target_link_libraries( raisin -ldl -ltinfo -lpthread clang clangAST
# clangAnalysis clangBasic clangDriver clangEdit clangIndex clangFrontend
# clangFrontendTool clangLex clangParse clangSema clangEdit clangASTMatchers
# clangRewrite clangRewriteFrontend clangStaticAnalyzerFrontend
# clangStaticAnalyzerCheckers clangStaticAnalyzerCore clangSerialization
# clangToolingCore clangTooling )

file(GLOB_RECURSE RAISIN_HEADERS "*.hpp")

lizard(
	TARGET raisin
	ADDITIONAL_FILES
		${RAISIN_HEADERS}
	ARGS
		--languages cpp
		--sort cyclomatic_complexity
	)

iwyu(
	TARGET raisin
	ARGS
		--std=c++17 # Useless with -p ?
#		-p="${CMAKE_BINARY_DIR}" # Outdated iwyu version.
		-Xiwyu
		--no_comments
	)

clang_tidy(
	TARGET raisin
	ARGS
		-p="${CMAKE_BINARY_DIR}"
	-checks=*
	)

clang_format(
	TARGET raisin
	ADDITIONAL_FILES
		${RAISIN_HEADERS}
	ARGS
	)

cppcheck(
	TARGET raisin
	ADDITIONAL_FILES
		${RAISIN_HEADERS}
	ARGS
#		--enable=all
		-v
	)

enable_clang_build_analyzer(TARGET raisin)

enable_sanitizers(TARGET raisin)
