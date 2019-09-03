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
include(CheckCXXCompilerFlag)
include(CMakePushCheckState)

add_library(CodeCoverage::all INTERFACE IMPORTED)
set(CodeCoverage_FOUND OFF)

if(TARGET CodeCoverage::${${PROJECT_NAME}_CODE_COVERAGE} OR ${${PROJECT_NAME}_CODE_COVERAGE} STREQUAL "Off")
   return()
endif()

cmake_push_check_state(RESET)

if(${PROJECT_NAME}_CODE_COVERAGE STREQUAL "LLVMSourceCoverage")
   set(coverage_compile_flags "-fprofile-instr-generate;-fcoverage-mapping")
   list(APPEND CMAKE_REQUIRED_FLAGS ${coverage_compile_flags})
   check_cxx_compiler_flag(-fprofile-instr-generate profiling_coverage_supported)
   check_cxx_compiler_flag(-fcoverage-mapping mapping_coverage_supported)
   if(${profiling_coverage_supported} AND ${mapping_coverage_supported})
      set(coverage_supported TRUE)
   endif()
elseif(${PROJECT_NAME}_CODE_COVERAGE STREQUAL "gcov")
   set(coverage_compile_flags "--coverage")
   set(coverage_link_flags ${coverage_compile_flags})
   list(APPEND CMAKE_REQUIRED_FLAGS ${coverage_compile_flags})
   check_cxx_compiler_flag(--coverage coverage_supported)
elseif(${PROJECT_NAME}_CODE_COVERAGE STREQUAL "SanitizerCoverage")
   message(FATAL_ERROR "Not yet implemented.")
else()
   message(FATAL_ERROR "Logic error: got ${PROJECT_NAME}_CODE_COVERAGE=\"${${PROJECT_NAME}_CODE_COVERAGE}\"")
endif()

cmake_pop_check_state()

if (${coverage_supported})
   add_library(CodeCoverage::${${PROJECT_NAME}_CODE_COVERAGE} INTERFACE IMPORTED)
   set_target_properties(
      CodeCoverage::${${PROJECT_NAME}_CODE_COVERAGE}
      PROPERTIES
         INTERFACE_COMPILE_OPTIONS "${coverage_compile_flags}"
         INTERFACE_LINK_LIBRARIES "${coverage_link_flags}")
   set(CodeCoverage_${${PROJECT_NAME}_CODE_COVERAGE}_FOUND ${coverage_supported})
   set(CodeCoverage_FOUND ${coverage_supported})
   set_property(TARGET CodeCoverage::all APPEND PROPERTY
      INTERFACE_LINK_LIBRARIES CodeCoverage::${${PROJECT_NAME}_CODE_COVERAGE})
endif()

find_package_handle_standard_args(CodeCoverage
   REQUIRED_VARS CodeCoverage_FOUND)
