# Copyright (c) Christopher Di Bella.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

### This selection of tests is used to check that a type that meets all but one of the requirements
### for an iterator concept does, in fact, not satisfy the concept.
###
add_subdirectory(iterator)
add_subdirectory(output)
add_subdirectory(forward)
add_subdirectory(bidirectional)
add_subdirectory(random_access)
add_subdirectory(contiguous)

add_subdirectory(sentinel)
add_subdirectory(sized_sentinel)
