# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
include(CMakeFindDependencyMacro)

# Same syntax as find_package
find_dependency(MYDEP REQUIRED)

# Add the targets file
include("${CMAKE_CURRENT_LIST_DIR}/ranges-targets.cmake")
