// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <cjdb/concepts/core/same_as.hpp>

static_assert(cjdb::same_as<int, decltype(0)>);

int main() {}
