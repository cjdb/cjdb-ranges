#
#  Copyright 2018 Morris Hafner
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

add_library(Sanitizer::all INTERFACE IMPORTED)
set(Sanitizer_FOUND ON)

foreach(san ${Sanitizer_FIND_COMPONENTS})
   if(TARGET Sanitizer::${san})
      continue()
   endif()

   cmake_push_check_state(RESET)

   set(sanitizer_option "")
   if(${san} MATCHES "Address")
      set(sanitizer_option "address")
   elseif(${san} MATCHES "Thread")
      set(sanitizer_option "thread")
   elseif(${san} MATCHES "Memory")
      set(sanitizer_option "memory")
      list(APPEND CMAKE_REQUIRED_FLAGS -fno-omit-frame-pointer)
      if(${san} MATCHES "Origins")
         list(APPEND CMAKE_REQUIRED_FLAGS -fsanitize-memory-track-origins=2)
      endif()
   elseif(${san} MATCHES "Undefined")
      set(sanitizer_option "undefined")
   elseif(${san} STREQUAL "DataFlow")
      set(sanitizer_option "dataflow")
   elseif(${san} STREQUAL "Leak")
      set(sanitizer_option "leak")
   elseif(${san} STREQUAL "ControlFlowIntegrity")
      if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
         continue()
      endif()
      list(APPEND CMAKE_REQUIRED_FLAGS "-fvisibility=default -flto")
      set(sanitizer_option "cfi")
   elseif(${san} STREQUAL "ShadowCallStack")
      set(sanitizer_option "shadow-call-stack")
   elseif(${san} STREQUAL "SafeStack")
      set(sanitizer_option "safe-stack")
   else()
      message(SEND_ERROR "${san} has not been implemented in FindSanitizer.cmake.")
   endif()

   list(APPEND CMAKE_REQUIRED_LIBRARIES -fsanitize=${sanitizer_option})

   check_cxx_compiler_flag(-fsanitize=${sanitizer_option} ${san}_supported)
   cmake_pop_check_state()

   if(${${san}_supported})
      add_library(Sanitizer::${san} INTERFACE IMPORTED)
      set_target_properties(Sanitizer::${san} PROPERTIES
                       INTERFACE_COMPILE_OPTIONS -fsanitize=${sanitizer_option}
                       INTERFACE_LINK_LIBRARIES -fsanitize=${sanitizer_option})
      set(Sanitizer_${san}_FOUND TRUE)
      set_property(TARGET Sanitizer::all APPEND PROPERTY
         INTERFACE_LINK_LIBRARIES Sanitizer::${san})
   endif()
endforeach()

find_package_handle_standard_args(Sanitizer
   REQUIRED_VARS Sanitizer_FOUND
   HANDLE_COMPONENTS)
