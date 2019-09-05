#
#  Copyright 2019 Christopher Di Bella
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
include(FindPackageHandleStandardArgs)

if((NOT ${${PROJECT_NAME}_ENABLE_CLANG_TIDY}) OR (${PROJECT_NAME}_CLANG_TIDY_PATH STREQUAL ""))
   if(NOT ${${PROJECT_NAME}_ENABLE_CLANG_TIDY})
      message(STATUS "clang-tidy disabled.")
   else()
      message(STATUS "No path for clang-tidy.")
   endif()
   set(CMAKE_CXX_CLANG_TIDY "")
   return()
endif()

if(EXISTS "${${PROJECT_NAME}_CLANG_TIDY_PATH}")
   find_package(Clang REQUIRED)
   set(ClangTidy_FOUND On)
   set(CMAKE_CXX_CLANG_TIDY "${${PROJECT_NAME}_CLANG_TIDY_PATH}" -p=${CMAKE_BINARY_DIR})
   message(STATUS "Found ${${PROJECT_NAME}_CLANG_TIDY_PATH}")
else()
   set(ClangTidy_FOUND Off)
   message(STATUS "${PROJECT_NAME}_CLANG_TIDY_PATH=\"${${PROJECT_NAME}_CLANG_TIDY_PATH}\" not found.")
endif()

find_package_handle_standard_args(ClangTidy
   REQUIRED_VARS ClangTidy_FOUND)
