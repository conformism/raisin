# cmake -DLLVM_DIR="/usr/lib/llvm-10/lib/cmake/llvm" -DClang_DIR="/usr/lib/llvm-10/lib/cmake/clang" ..

cmake_minimum_required( VERSION 3.16 )

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

include( CPM )

CPMAddPackage(
	NAME cmake-utils
	GITHUB_REPOSITORY conformism/cmake-utils
	GIT_TAG main
	DOWNLOAD_ONLY
	)

list( APPEND CMAKE_MODULE_PATH
	"${FETCHCONTENT_BASE_DIR}/cmake-utils-src"
	)

set( CMAKE_UTILS * )
set( COVERAGE_GLOBAL_ONLY ON )
include( CMakeUtils )

add_subdirectory( "${CMAKE_SOURCE_DIR}/icon" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/src" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/test" )

coverage_global()
codechecker(
	GLOBAL
	NO_CTU
	SKIP
		+${CMAKE_SOURCE_DIR}/src
		+${CMAKE_SOURCE_DIR}/test/unit
		-*
	ARGS
		"${CMAKE_BINARY_DIR}/compile_commands.json"
		-j 4
	ADDITIONAL_OPTIONAL_REPORTS
		"${CMAKE_BINARY_DIR}/src/CMakeFiles/raisin_cppcheck.dir/codechecker_reports"
	)
