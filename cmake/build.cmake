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

# \brief Provides build settings common for all targets.
# \param target The target to apply the target to.
#
function(build_impl target)
   target_compile_options("${target}" PUBLIC
      -fdiagnostics-color=always
      $<$<CXX_COMPILER_ID:GNU>:
         -fconcepts>
      $<$<CXX_COMPILER_ID:Clang>:
         -Xclang
         -fconcepts-ts>)
   target_compile_options("${target}" PRIVATE
      $<$<CXX_COMPILER_ID:GNU>:
         -Wlogical-op>
      $<$<CONFIG:Debug>:
         -fstack-protector-all>)

   if(CJDB_AUDIT_CONTRACTS)
      target_compile_definitions(CJDB_AUDIT_CONTRACTS)
   endif()

   target_include_directories("${target}" PUBLIC "${PROJECT_SOURCE_DIR}/include")
   target_link_libraries("${target}" PUBLIC MicrosoftGSL::gsl)
endfunction()

# \brief Produces a target name for compiling a translation unit.
# \param prefix A string that prefixes the filename that will be removed from its path. Everything
#               that prefixes the prefix will _also_ be removed.
# \param file The name of the source file.
# \returns A sans-prefix path that is dot separated.
#
function(name_target prefix file)
   get_filename_component(sublibrary "${file}.cpp" ABSOLUTE)
   string(REGEX REPLACE ".cpp$" "" sublibrary "${sublibrary}")
   string(REPLACE "/" "." sublibrary "${sublibrary}")
   string(REGEX REPLACE "^.*${prefix}[.]" "" sublibrary "${sublibrary}")

   if(${sublibrary} MATCHES "^.data")
      message(FATAL_ERROR "${sublibrary}")
   endif()
   set(target "${sublibrary}" PARENT_SCOPE)
endfunction()

# \brief Builds an executable.
# \param prefix A string that prefixes the filename that will be removed from its path. Everything
#               that prefixes the prefix will _also_ be removed.
# \param file The name of the source file.
#
function(build_executable prefix file)
   name_target("${prefix}" "${file}")
   add_executable("${target}" "${file}.cpp")
   build_impl("${target}")

   target_link_libraries("${target}" PUBLIC
      $<$<CONFIG:Debug>:Sanitizer::all>)
endfunction()

# \brief Builds a library.
# \param prefix A string that prefixes the filename that will be removed from its path. Everything
#               that prefixes the prefix will _also_ be removed.
# \param file The name of the source file.
#
function(build_library prefix file)
   name_target("${prefix}" "${file}")
   add_library("${target}" "${file}.cpp")
   build_impl("${target}")
endfunction()

set(enable_catch2 On)
set(disable_catch2 Off)

# \brief Builds a test executable and creates a test target (for CTest).
# \param prefix A string that prefixes the filename that will be removed from its path. Everything
#               that prefixes the prefix will _also_ be removed.
# \param file The name of the source file.
# \param catch2_enabled A boolean to determine if Catch2 should be linked or not.
#
function(build_test prefix file catch2_enabled)
   build_executable("${prefix}" "${file}")
   name_target("${prefix}" "${file}")

   if(catch2_enabled)
      target_link_libraries("${target}" PRIVATE "cjdbstdlib.test.catch2_main")
   endif()

   add_test("test.${target}" "${target}")
endfunction()

# \brief Builds a benchmark executable and creates a test target (for CTest).
# \param prefix A string that prefixes the filename that will be removed from its path. Everything
#               that prefixes the prefix will _also_ be removed.
# \param file The name of the source file.
# \param catch2_enabled A boolean to determine if Catch2 should be linked or not.
#
function(build_benchmark prefix file)
   build_executable("${prefix}" "${file}")
   name_target("${prefix}" "${file}")
   target_link_libraries("${target}" PRIVATE benchmark::benchmark)
   add_test("benchmark.${target}" "${target}")
endfunction()
