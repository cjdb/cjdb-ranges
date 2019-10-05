# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
target_include_directories(
   ${PROJECT_NAME}
   INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)

target_include_directories(
   ${PROJECT_NAME}
   SYSTEM INTERFACE
   $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

install(TARGETS "${PROJECT_NAME}" EXPORT "${PROJECT_NAME}-targets" DESTINATION lib)
install(
   EXPORT "${PROJECT_NAME}-targets"
   FILE "${PROJECT_NAME}-config.cmake"
   DESTINATION "lib/cmake/${PROJECT_NAME}")
install(DIRECTORY "include/" DESTINATION "include" FILES_MATCHING PATTERN "*.hpp")
export(EXPORT "${PROJECT_NAME}-targets" FILE "${PROJECT_NAME}-config.cmake")
