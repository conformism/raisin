# cmake -DLLVM_DIR="/usr/lib/llvm-10/lib/cmake/llvm" -DClang_DIR="/usr/lib/llvm-10/lib/cmake/clang" ..

cmake_minimum_required( VERSION 3.11 )

project( Raisin
	LANGUAGES CXX
	VERSION 0.0.1
	DESCRIPTION "Produce CFG from a C++ source code"
	)

list( APPEND CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/cmake"
	)

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "Release" )
endif()
message( STATUS "Build type: ${CMAKE_BUILD_TYPE}" )

find_package( Clang REQUIRED )

message( STATUS "LLVM version: ${LLVM_PACKAGE_VERSION}" )
message( STATUS "Using ClangConfig.cmake in: ${Clang_DIR}" )
message( STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}" )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( SOURCES
	"${CMAKE_SOURCE_DIR}/src/domain/cfg/element/element.cpp"
	"${CMAKE_SOURCE_DIR}/src/domain/cfg/block/block.cpp"
	"${CMAKE_SOURCE_DIR}/src/domain/cfg/scope/scope.cpp"
	"${CMAKE_SOURCE_DIR}/src/domain/cfg/cfg.cpp"
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
	)

add_executable( ${PROJECT_NAME} ${SOURCES} )

target_compile_definitions( ${PROJECT_NAME}
	PRIVATE
#	${LLVM_DEFINITIONS}
#	${CLANG_DEFINITIONS}
	)

target_compile_features( ${PROJECT_NAME}
	PRIVATE
	cxx_std_17
	)

target_compile_options( ${PROJECT_NAME}
	PRIVATE
	$<$<CONFIG:Debg>:-Wall>
	$<$<CONFIG:Debug>:-Wextra>
	)

target_include_directories( ${PROJECT_NAME}
	PRIVATE
	"${CMAKE_SOURCE_DIR}/src"
#	${LLVM_INCLUDE_DIRS}
	${CLANG_INCLUDE_DIRS}
	)

target_link_libraries( ${PROJECT_NAME}
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

set_target_properties( ${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "raisin"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out"
	)

add_subdirectory( "${CMAKE_SOURCE_DIR}/icon" )
# add_subdirectory( "${CMAKE_SOURCE_DIR}/test" )
