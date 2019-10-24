# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
cmake_minimum_required(VERSION 3.14)

project("ranges" CXX)
add_library(${PROJECT_NAME} INTERFACE)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include("${CMAKE_BINARY_DIR}/conan_paths.cmake" REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/config/cmake")

# Project configuration
target_include_directories(ranges INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

enable_testing()
include(CTest)

find_package(constexpr-contracts REQUIRED)

# clang-tidy options
option(CJDB_RANGES_ENABLE_CLANG_TIDY "Builds with clang-tidy, if available. Defaults to On." On)
set(CJDB_RANGES_CLANG_TIDY_PATH "/usr/bin/clang-tidy" CACHE
	STRING "Sets the path for clang-tidy. Defaults to \"/usr/bin/clang-tidy\".")

if(CJDB_RANGES_ENABLE_CLANG_TIDY)
	find_package(ClangTidy REQUIRED)
endif()

include(add-targets)

add_subdirectory(test)

# Include

include(CMakePackageConfigHelpers)
install(TARGETS ranges
        EXPORT cjdb-ranges
        DESTINATION lib)
install(EXPORT cjdb-ranges
        FILE cjdb-ranges-config.cmake
        NAMESPACE cjdb::
        DESTINATION lib/cmake/cjdb-ranges)
install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*")
export(EXPORT cjdb-ranges FILE cjdb-ranges-config.cmake)
