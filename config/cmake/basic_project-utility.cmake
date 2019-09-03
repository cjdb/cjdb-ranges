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

# Allows a long string to be split over multiple lines.
#
macro(BASIC_PROJECT_MULTILINE_STRING name)
   set(${name} ${ARGN})
   string(REPLACE ":" " " ${name} ${${name}})
endmacro()

# Sanity checks a user option.
#
function(basic_project_enumerated_option)
   set(optional_values LIST)
   set(single_value_args OPTION_NAME TYPE)
   set(multi_value_args DEFAULT_VALUE DESCRIPTION EXPECTS)

   cmake_parse_arguments(
      OPTION_DECLARATOR
      "${optional_values}"
      "${single_value_args}"
      "${multi_value_args}"
      ${ARGN}
   )

   if(NOT OPTION_DECLARATOR_DEFAULT_VALUE)
      set(default_description "")
   else()
      set(default_description "Defaults to \"${OPTION_DECLARATOR_DEFAULT_VALUE}\".")
   endif()

   set(option_description
      "${${OPTION_DECLARATOR_DESCRIPTION}}. Valid options are ${OPTION_DECLARATOR_EXPECTS}. ${default_description}")
   set(
      "${OPTION_DECLARATOR_OPTION_NAME}"
      "${OPTION_DECLARATOR_DEFAULT_VALUE}" CACHE
      "${OPTION_DECLARATOR_TYPE}" "${option_description}"
   )

   if(${OPTION_DECLARATOR_LIST})
      foreach(i ${${OPTION_DECLARATOR_OPTION_NAME}})
         if (NOT ${i} IN_LIST OPTION_DECLARATOR_EXPECTS)
            message(
               FATAL_ERROR
               "${OPTION_DECLARATOR_OPTION_NAME} contains invalid value \"${i}\". It must be one of ${OPTION_DECLARATOR_EXPECTS}."
            )
         endif()
      endforeach()
   else()
      if (NOT ${${OPTION_DECLARATOR_OPTION_NAME}} IN_LIST OPTION_DECLARATOR_EXPECTS)
         message(
            FATAL_ERROR
            "${OPTION_DECLARATOR_OPTION_NAME} was set to \"${${OPTION_DECLARATOR_OPTION_NAME}}\". It must be one of ${OPTION_DECLARATOR_EXPECTS}."
         )
      endif()
   endif()
endfunction()
