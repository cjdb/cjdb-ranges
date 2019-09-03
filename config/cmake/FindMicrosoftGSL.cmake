#
#  Copyright Christopher Di Bella
#  Author: Morris Hafner
#
#  Description:
#    Checks that ${LIBRARY} for the target system is installed and can be found in CMAKE_PREFIX_PATH
#    or ${LIBRARY}_ROOT. Defines the following imported targets:
#        MicrosoftGSL::GSL (requires C++11)
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

if(TARGET MicrosoftGSL::gsl)
   return()
endif()

find_path(MicrosoftGSL_INCLUDE_DIRS gsl/gsl)

find_package_handle_standard_args(MicrosoftGSL
   REQUIRED_VARS MicrosoftGSL_INCLUDE_DIRS)

add_library(MicrosoftGSL::gsl INTERFACE IMPORTED)
set_target_properties(MicrosoftGSL::gsl PROPERTIES
   INTERFACE_INCLUDE_DIRECTORIES ${MicrosoftGSL_INCLUDE_DIRS}
INTERFACE_COMPILE_FEATURES cxx_std_11)
