#
#  Copyright 2018 Christopher Di Bella
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

function(add_impl_linkage target scope to_link)
   if(to_link)
      message(STATUS "Linking `${to_link}` with ${scope} scope, against ${target}.")
      target_link_libraries("${target}" ${scope} "${to_link}")
   endif()
endfunction()

function(add_impl_suffix_include target scope to_include)
   if(to_include)
      message(STATUS
         "Suffixing `${to_include}` to include directories, with ${scope} scope, when compiling ${target}.")
      target_include_directories("${target}" ${scope} "${to_include}")
   endif()
endfunction()

function(add_impl_suffix_options target scope to_suffix)
   if(to_suffix)
      message(STATUS
         "Suffixing compiler option(s) `${to_suffix}` with ${scope} scope, when compiling ${target}.")
      target_compile_options("${target}" ${scope} "${to_suffix}")
   endif()
endfunction()

function(add_impl_enable_features target scope to_enable)
   if(to_enable)
      message(STATUS
         "Enabling compiler feature(s) `${to_enable}` with ${scope} scope, when compiling ${target}.")
      target_compile_features("${target}" ${scope} "${to_enable}")
   endif()
endfunction()

function(add_impl_define_macros target scope to_define)
   if(to_define)
      message(STATUS
         "Defining macro(s) `${to_define}` with ${scope} scope, when compiling ${target}")
      target_compile_definitions("${target}" ${scope} "${to_define}")
   endif()
endfunction()

function(add_impl_custom_target_settings)
   set(optional_values "")
   set(single_value_args TARGET SCOPE)
   set(multi_value_args LINK SUFFIX_INCLUDE SUFFIX_OPTIONS ENABLE_FEATURE DEFINITIONS)
   cmake_parse_arguments(
      settings
      "${optional_values}"
      "${single_value_args}"
      "${multi_value_args}"
      ${ARGN})

   add_impl_suffix_include("${settings_TARGET}" "${settings_SCOPE}" "${settings_SUFFIX_INCLUDE}")
   add_impl_suffix_options("${settings_TARGET}" "${settings_SCOPE}" "${settings_SUFFIX_OPTIONS}")
   add_impl_enable_features("${settings_TARGET}" "${settings_SCOPE}" "${settings_ENABLE_FEATURES}")
   add_impl_define_macros("${settings_TARGET}" "${settings_SCOPE}" "${settings_DEFINITIONS}")
   add_impl_linkage("${settings_TARGET}" "${settings_SCOPE}" "${settings_LINK}")
endfunction()

macro(BASIC_PROJECT_EXTRACT_ADD_TARGET_ARGS_LIBRARIES)
   set(optional_values "")
   set(single_value_args TARGET)
   set(multi_value_args

      INCLUDE
      INTERFACE_INCLUDE
      PUBLIC_INCLUDE

      LINK
      INTERFACE_LINK
      PUBLIC_LINK

      COMPILER_OPTIONS
      INTERFACE_COMPILER_OPTIONS
      PUBLIC_COMPILER_OPTIONS

      COMPILER_FEATURES
      INTERFACE_COMPILER_FEATURES
      PUBLIC_COMPILER_FEATURES

      COMPILER_DEFINITIONS
      INTERFACE_COMPILER_DEFINITIONS
      PUBLIC_COMPILER_DEFINITIONS)

   cmake_parse_arguments(
      add_target_args
      "${optional_values}"
      "${single_value_args}"
      "${multi_value_args}"
      ${ARGN})
endmacro()

# \brief Provides build settings common for all targets.
# \param target The target to apply the target to.
#
function(add_impl)
   BASIC_PROJECT_EXTRACT_ADD_TARGET_ARGS_LIBRARIES(${ARGN})

   # Compiler features
   target_compile_options("${add_target_args_TARGET}" PRIVATE
      $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
         -fvisibility=default
         -fstack-protector
         $<$<CONFIG:Debug>:
            -fstack-protector-all>
      >)

   target_include_directories("${add_target_args_TARGET}" PUBLIC "${PROJECT_SOURCE_DIR}/include")

   add_impl_custom_target_settings(
      TARGET         "${add_target_args_TARGET}"
      SCOPE PUBLIC
      SUFFIX_INCLUDE "${add_target_args_PUBLIC_INCLUDE}"
      SUFFIX_OPTIONS "${add_target_args_PUBLIC_COMPILER_OPTIONS}"
      ENABLE_FEATURE "${add_target_args_PUBLIC_COMPILER_FEATURES}"
      DEFINITIONS    "${add_target_args_PUBLIC_COMPILER_DEFINITIONS}"
      LINK           "${add_target_args_PUBLIC_LINK}")
   add_impl_custom_target_settings(
      TARGET         "${add_target_args_TARGET}"
      SCOPE PRIVATE
      SUFFIX_INCLUDE "${add_target_args_INCLUDE}"
      SUFFIX_OPTIONS "${add_target_args_COMPILER_OPTIONS}"
      ENABLE_FEATURE "${add_target_args_COMPILER_FEATURES}"
      DEFINITIONS    "${add_target_args_COMPILER_DEFINITIONS}"
      LINK           "${add_target_args_LINK}")
   add_impl_custom_target_settings(
      TARGET         "${add_target_args_TARGET}"
      SCOPE INTERFACE
      SUFFIX_INCLUDE "${add_target_args_INTERFACE_INCLUDE}"
      SUFFIX_OPTIONS "${add_target_args_INTERFACE_COMPILER_OPTIONS}"
      ENABLE_FEATURE "${add_target_args_INTERFACE_COMPILER_FEATURES}"
      DEFINITIONS    "${add_target_args_INTERFACE_COMPILER_DEFINITIONS}"
      LINK           "${add_target_args_INTERFACE_LINK}")
endfunction()

# \brief Produces a target name for compiling a translation unit.
# \param prefix A string that prefixes the filename that will be removed from its path. Everything
#               that prefixes the prefix will _also_ be removed.
# \param file The name of the source file.
# \returns A sans-prefix path that is dot separated.
#
function(name_target filename)
   get_filename_component(sublibrary "${filename}" ABSOLUTE)
   string(REGEX REPLACE "[.][^.]+$" "" sublibrary "${sublibrary}")
   string(REPLACE "/" "." sublibrary "${sublibrary}")
   string(REPLACE "/" "." remove_prefix "${CMAKE_SOURCE_DIR}")
   string(REGEX REPLACE "^.*${remove_prefix}[.]" "" sublibrary "${sublibrary}")
   set(target "${sublibrary}" PARENT_SCOPE)
endfunction()

macro(BASIC_PROJECT_EXTRACT_ADD_TARGET_ARGS)
   set(optional_values "")
   set(single_value_args FILENAME LIBRARY_TYPE)
   set(multi_value_args

      PUBLIC_INCLUDE
      INCLUDE
      INTERFACE_INCLUDE

      PUBLIC_LINK
      LINK
      INTERFACE_LINK

      PUBLIC_COMPILER_OPTIONS
      COMPILER_OPTIONS
      INTERFACE_COMPILER_OPTIONS

      PUBLIC_COMPILER_FEATURES
      COMPILER_FEATURES
      INTERFACE_COMPILER_FEATURES

      PUBLIC_COMPILER_DEFINITIONS
      COMPILER_DEFINITIONS
      INTERFACE_COMPILER_DEFINITIONS)

   cmake_parse_arguments(
      add_target_args
      "${optional_values}"
      "${single_value_args}"
      "${multi_value_args}"
      ${ARGN})

   if(${add_target_args_FILENAME} STREQUAL "")
      BASIC_PROJECT_MULTILINE_STRING(
         error
         "FILENAME is not set. Cannot build a target without a filename.")
      message(FATAL_ERROR "${error}")
   endif()
endmacro()

macro(BASIC_PROJECT_CALL_ADD_IMPL)
   add_impl(
      TARGET "${target}"

      INCLUDE "${add_target_args_INCLUDE}"
      INTERFACE_INCLUDE "${add_target_args_INTERFACE_INCLUDE}"
      PUBLIC_INCLUDE "${add_target_args_PUBLIC_INCLUDE}"

      LINK "${add_target_args_LINK}"
      INTERFACE_LINK "${add_target_args_INTERFACE_LINK}"
      PUBLIC_LINK "${add_target_args_PUBLIC_LINK}"

      COMPILER_OPTIONS "${add_target_args_COMPILER_OPTIONS}"
      INTERFACE_COMPILER_OPTIONS "${add_target_args_INTERFACE_COMPILER_OPTIONS}"
      PUBLIC_COMPILER_OPTIONS "${add_target_args_PUBLIC_COMPILER_OPTIONS}"

      COMPILER_FEATURES "${add_target_args_COMPILER_FEATURES}"
      INTERFACE_COMPILER_FEATURES "${add_target_args_INTERFACE_COMPILER_FEATURES}"
      PUBLIC_COMPILER_FEATURES "${add_target_args_PUBLIC_COMPILER_FEATURES}"

      COMPILER_DEFINITIONS "${add_target_args_COMPILER_DEFINITIONS}"
      INTERFACE_COMPILER_DEFINITIONS "${add_target_args_INTERFACE_COMPILER_DEFINITIONS}"
      PUBLIC_COMPILER_DEFINITIONS "${add_target_args_PUBLIC_COMPILER_DEFINITIONS}"
   )
endmacro()

# \see add_${PROJECT_NAME}_executable
#
function(add_basic_project_executable_impl)
   BASIC_PROJECT_EXTRACT_ADD_TARGET_ARGS(${ARGN})

   name_target("${add_target_args_FILENAME}")
   add_executable("${target}" "${add_target_args_FILENAME}")
   BASIC_PROJECT_CALL_ADD_IMPL()
endfunction()

# \see add_${PROJECT_NAME}_library
#
function(add_basic_project_library_impl)
   BASIC_PROJECT_EXTRACT_ADD_TARGET_ARGS(${ARGN})

   name_target("${add_target_args_FILENAME}")

   set(legal_library_types "" STATIC SHARED MODULE OBJECT)
   list(FIND legal_library_types "${add_target_args_LIBRARY_TYPE}" library_type_result)
   if(${library_type_result} EQUAL -1)
      message(FATAL_ERROR "Cannot add a library of type \"${add_target_args_LIBRARY_TYPE}\"")
   endif()

   add_library("${target}" ${add_target_args_LIBRARY_TYPE} "${add_target_args_FILENAME}")
   BASIC_PROJECT_CALL_ADD_IMPL()
endfunction()

# \see add_${PROJECT_NAME}_test
#
function(add_basic_project_test_impl)
   add_basic_project_executable_impl(${ARGN})

   BASIC_PROJECT_EXTRACT_ADD_TARGET_ARGS(${ARGN})
   name_target("${add_target_args_FILENAME}")
   add_test("test.${target}" "${target}")
endfunction()
