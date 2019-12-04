// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Checks that the names expected when one includes "cjdb/range.hpp" actually exist.
// Does not check for functionality.
//
#include "cjdb/range.hpp"

using cjdb::ranges::begin; // NOLINT(misc-unused-using-decls)
using cjdb::ranges::cbegin; // NOLINT(misc-unused-using-decls)
// using cjdb::ranges::rbegin;
// using cjdb::ranges::crbegin;

using cjdb::ranges::end; // NOLINT(misc-unused-using-decls)
using cjdb::ranges::cend; // NOLINT(misc-unused-using-decls)
// using cjdb::ranges::rend;
// using cjdb::ranges::crend;

// using cjdb::ranges::data;
// using cjdb::ranges::cdata;

// using cjdb::ranges::size;

int main()
{}
