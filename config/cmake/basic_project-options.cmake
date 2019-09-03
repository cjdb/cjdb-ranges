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

# clang-tidy options
option(${PROJECT_NAME}_ENABLE_CLANG_TIDY "Builds with clang-tidy, if available. Defaults to On." On)

set(${PROJECT_NAME}_CLANG_TIDY_PATH "/usr/bin/clang-tidy" CACHE
   STRING "Sets the path for clang-tidy. Defaults to \"/usr/bin/clang-tidy\".")

# Options for sanitizers
set(valid_sanitizer_options
   ""
   Address              # see https://clang.llvm.org/docs/AddressSanitizer.html
   Thread               # see https://clang.llvm.org/docs/ThreadSanitizer.html
   Memory               # see https://clang.llvm.org/docs/MemorySanitizer.html
   MemoryWithOrigins    # see https://clang.llvm.org/docs/MemorySanitizer.html#origin-tracking
   Undefined            # see https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
   DataFlow             # see https://clang.llvm.org/docs/DataFlowSanitizer.html
   Leak                 # see https://clang.llvm.org/docs/LeakSanitizer.html
   ControlFlowIntegrity # see https://clang.llvm.org/docs/ControlFlowIntegrity.html
   ShadowCallStack      # see https://clang.llvm.org/docs/ShadowCallStack.html
   SafeStack            # see https://clang.llvm.org/docs/SafeStack.html
)
basic_project_enumerated_option(
   OPTION_NAME ${PROJECT_NAME}_REQUIRED_SANITIZERS
   DESCRIPTION
      "Enables a list of sanitizers in Debug mode."
      "The list of sanitizers must be available to the compiler."
      "ControlFlowIntegrity is not enabled in Debug mode: it is only enabled in Release modes."
   TYPE STRING LIST
   EXPECTS ${valid_sanitizer_options}
   DEFAULT_VALUE "")

basic_project_enumerated_option(
   OPTION_NAME ${PROJECT_NAME}_OPTIONAL_SANITIZERS
   DESCRIPTION
      "Enables a list of sanitizers in Debug mode."
      "Sanitizers not available to the compiler are ignored."
      "ControlFlowIntegrity is not enabled in Debug mode: it is only enabled in Release modes."
   TYPE STRING LIST
   EXPECTS ${valid_sanitizer_options}
   DEFAULT_VALUE Address Undefined ControlFlowIntegrity)

option(${PROJECT_NAME}_SANITIZE_RELEASE "Turns on sanitizers in Release modes. Defaults to Off." Off)

# Coverage options
basic_project_enumerated_option(
   OPTION_NAME ${PROJECT_NAME}_CODE_COVERAGE
   DESCRIPTION "Enables/disables code coverage. Options are Off, GCov, and LLVMSourceCoverage."
   TYPE STRING LIST
   EXPECTS Off gcov LLVMSourceCoverage SanitizerCoverage
   DEFAULT_VALUE Off)
