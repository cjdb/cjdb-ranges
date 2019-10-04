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
# \brief Provides build settings common for all targets.
# \param target The target to apply the target to.
#
function(add_impl)
	set(optional_values "")
	set(single_value_args TARGET)
	set(multi_value_args INCLUDE LINK COMPILER_OPTIONS COMPILER_DEFINITIONS)

	cmake_parse_arguments(add_target_args
	                      "${optional_values}"
	                      "${single_value_args}"
	                      "${multi_value_args}"
	                      ${ARGN})

	# Compiler features
	target_compile_options("${add_target_args_TARGET}" PRIVATE
	   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
	      -fvisibility=default
	      -fstack-protector
	      $<$<CONFIG:Debug>:
	         -fstack-protector-all>
	   >)

	target_include_directories("${add_target_args_TARGET}"
	                           PUBLIC
	                           "${PROJECT_SOURCE_DIR}/include")
	target_include_directories("${add_target_args_TARGET}"
	                           PRIVATE
	                           "${add_target_args_INCLUDE}")
	target_compile_options("${add_target_args_TARGET}"
	                       PRIVATE
	                       "${add_target_args_COMPILER_OPTIONS}")
	target_compile_definitions("${add_target_args_TARGET}"
	                           PRIVATE
	                           "${add_target_args_COMPILER_DEFINITIONS}")
	target_link_libraries("${add_target_args_TARGET}"
	                      PRIVATE
	                      "${add_target_args_LINK}")
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
	set(multi_value_args INCLUDE LINK COMPILER_OPTIONS COMPILER_DEFINITIONS)

	cmake_parse_arguments(add_target_args
	                      "${optional_values}"
	                      "${single_value_args}"
	                      "${multi_value_args}"
	                      ${ARGN})

	if(${add_target_args_FILENAME} STREQUAL "")
		message(FATAL_ERROR "FILENAME is not set. Cannot build a target without a filename.")
	endif()
endmacro()

macro(BASIC_PROJECT_CALL_ADD_IMPL)
	add_impl(TARGET "${target}"
	         INCLUDE "${add_target_args_INCLUDE}"
	         LINK "${add_target_args_LINK}"
	         COMPILER_OPTIONS "${add_target_args_COMPILER_OPTIONS}"
	         COMPILER_DEFINITIONS "${add_target_args_COMPILER_DEFINITIONS}")
endmacro()
