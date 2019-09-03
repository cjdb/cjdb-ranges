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

# Check that incompatible sanitisers are not simultaneously enabled.
#
function(flag_incompatible_sanitizers required optional)
   set(joined "${required}")
   list(APPEND joined "${optional}")

   list(FIND joined "Address" asan_result)
   list(FIND joined "Thread" tsan_result)
   list(FIND joined "Memory" msan_result)
   list(FIND joined "MemoryWithOrigins" msan_origin_result)
   list(FIND joined "Undefined" ubsan_result)
   list(FIND joined "DataFlow" dataflow_result)
   list(FIND joined "Leak" lsan_result)
   list(FIND joined "ControlFlowIntegrity" cfi_result)
   list(FIND joined "ShadowCallStack" shadow_call_stack_result)
   list(FIND joined "SafeStack" safe_stack_result)

   if(asan_result GREATER -1)
      if(tsan_result GREATER -1)
         message(SEND_ERROR "Cannot enable both AddressSanitizer and ThreadSanitizer.")
      endif()

      if(msan_result GREATER -1 OR msan_origin_result GREATER -1)
         message(SEND_ERROR "Cannot enable both AddressSanitizer and MemorySanitizer.")
      endif()

      if(leak_result GREATER -1)
         message(SEND_ERROR "LeakSanitizer is already enabled by AddressSanitizer.")
      endif()

      if (shadow_call_stack_result GREATER -1)
         message(SEND_ERROR "Cannot enable both AddressSanitizer and ShadowCallStack.")
      endif()

      if(safe_stack_result GREATER -1)
         message(SEND_ERROR "Cannot enable both AddressSanitizer and SafeStack.")
      endif()
   endif()

   if(tsan_result GREATER -1)
      if(msan_result GREATER -1 OR msan_origin_result GREATER -1)
         message(SEND_ERROR "Cannot enable both ThreadSanitizer and MemorySanitizer.")
      endif()

      if(lsan_result GREATER -1)
         message(SEND_ERROR "Cannot enable both ThreadSanitizer and LeakSanitizer.")
      endif()

      if(shadow_call_stack_result GREATER -1)
         message(SEND_ERROR "Cannot enable both ThreadSanitizer and ShadowCallStack.")
      endif()

      if(safe_stack_result GREATER -1)
         message(SEND_ERROR "Cannot enable both ThreadSanitizer and SafeStackResult.")
      endif()
   endif()

   if(msan_result GREATER -1 OR msan_origin_result GREATER -1)
      if(msan_result GREATER -1 AND msan_origin_result GREATER -1)
         message(FATAL_ERROR "Both Memory and MemoryWithOrigins are listed: please choose one.")
      endif()

      if(leak_result GREATER -1)
         message(SEND_ERROR "Cannot enable both MemorySanitizer and LeakSanitizer.")
      endif()

      if(safe_stack_result GREATER -1)
         message(SEND_ERROR "Cannot enable both MemorySanitizer and SafeStack.")
      endif()
   endif()

   if(lsan_result GREATER -1)
      if(shadow_call_stack_result GREATER -1)
         message(SEND_ERROR "Cannot enable both LeakSanitizer and ShadowCallStack.")
      endif()

      if(safe_stack_result GREATER -1)
         message(SEND_ERROR "Cannot enable both LeakSanitizer and SafeStack.")
      endif()
   endif()

   if(shadow_call_stack_result GREATER -1 AND safe_stack_result GREATER -1)
      message(SEND_ERROR "Cannot enable both ShadowCallStack and SafeStack.")
   endif()
endfunction()

flag_incompatible_sanitizers(
   "${${PROJECT_NAME}_REQUIRED_SANITIZERS}"
   "${${PROJECT_NAME}_OPTIONAL_SANITIZERS}")

find_package(Sanitizer
   REQUIRED COMPONENTS ${${PROJECT_NAME}_REQUIRED_SANITIZERS}
   OPTIONAL_COMPONENTS ${${PROJECT_NAME}_OPTIONAL_SANITIZERS})
