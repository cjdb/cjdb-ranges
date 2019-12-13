# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
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
function(name_target filename proposed_target)
	get_filename_component(sublibrary "${filename}" ABSOLUTE)

	# use any proposed target name in place of the filename
	if (NOT ${proposed_target} STREQUAL "")
		string(REGEX REPLACE "${filename}$" "${proposed_target}" sublibrary "${sublibrary}")
	else()
		string(REGEX REPLACE "[.][^.]+$" "" sublibrary "${sublibrary}")
	endif()

	string(REPLACE "/" "." sublibrary "${sublibrary}")
	string(REPLACE "/" "." remove_prefix "${CMAKE_SOURCE_DIR}")
	string(REGEX REPLACE "^.*${remove_prefix}[.]" "" sublibrary "${sublibrary}")

	set(target "${sublibrary}" PARENT_SCOPE)
endfunction()

macro(BASIC_PROJECT_EXTRACT_ADD_TARGET_ARGS)
	set(optional_values "")
	set(single_value_args FILENAME TARGET LIBRARY_TYPE)
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
