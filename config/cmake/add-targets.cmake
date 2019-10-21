# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
include(add-targets-impl)

# \brief Builds an executable.
# \param prefix A string that prefixes the filename that will be removed from its path. Everything
#               that prefixes the prefix will _also_ be removed.
# \param file The name of the source file.
#
function(add_cjdblib_executable)
   BASIC_PROJECT_EXTRACT_ADD_TARGET_ARGS(${ARGN})

   name_target("${add_target_args_FILENAME}")
   add_executable("${target}" "${add_target_args_FILENAME}")
   BASIC_PROJECT_CALL_ADD_IMPL()
endfunction()

# \brief Builds a library.
# \param prefix A string that prefixes the filename that will be removed from its path. Everything
#               that prefixes the prefix will _also_ be removed.
# \param file The name of the source file.
#
function(add_cjdblib_library)
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



# \brief Builds a test executable and creates a test target (for CTest).
# \param prefix A string that prefixes the filename that will be removed from its path. Everything
#               that prefixes the prefix will _also_ be removed.
# \param file The name of the source file.
#
function(add_cjdblib_test)
   add_cjdblib_executable(${ARGN})

   BASIC_PROJECT_EXTRACT_ADD_TARGET_ARGS(${ARGN})
   name_target("${add_target_args_FILENAME}")
   add_test("test.${target}" "${target}")
endfunction()
