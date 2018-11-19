#
#  Copyright Christopher Di Bella
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

set(Concepts_FOUND ON)

cmake_push_check_state(RESET)
if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
   if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "8.1.0")
      message(FATAL_ERROR "GCC versions under 8.1.0 are not supported.")
   endif()

   set(cjdb_concepts_flags "-std=c++2a")
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
   if(NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_EQUAL "6.0.0")
      message(FATAL_ERROR "Only Saar Raz' branch supported is at present.")
   endif()

   set(cjdb_concepts_flags "-std=c++2a -Xclang -fconcepts-ts")
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC")
   set(cjdb_concepts_flags "/experimental:concepts")
else()
   message(FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} is not supported at present.")
endif()

set(CMAKE_REQUIRED_FLAGS "${cjdb_concepts_flags}")
check_cxx_source_compiles("template<class> concept Auto = true; int main() {}" cjdb_cxx20_concepts)
set(CMAKE_REQUIRED_FLAGS "")
cmake_pop_check_state()

add_library(Concepts::concept INTERFACE IMPORTED)
if(NOT "${cjdb_cxx20_concepts}")
   if(NOT ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
      message(FATAL_ERROR
         "${CMAKE_CXX_COMPILER_ID} does not support concepts; this project requires a concepts-savvy compiler.")
   endif()

   set_target_properties(Concepts::concept PROPERTIES
      INTERFACE_COMPILE_OPTIONS -fconcepts
      INTERFACE_COMPILE_DEFINITIONS concept=concept\ bool)
else()
   string(REPLACE " " ";" cjdb_concepts_flags ${cjdb_concepts_flags})
   foreach(flag ${cjdb_concepts_flags})
      set_property(TARGET Concepts::concept APPEND PROPERTY
         INTERFACE_COMPILE_OPTIONS ${flag})
   endforeach()
endif()
