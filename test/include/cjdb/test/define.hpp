// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TEST_DEFINE_HPP
#define CJDB_TEST_DEFINE_HPP

#define CJDB_TEST_CONCAT_IMPL(prefix, suffix) prefix ## suffix
#define CJDB_TEST_CONCAT(prefix, suffix) CJDB_TEST_CONCAT_IMPL(prefix, suffix)

#endif // CJDB_TEST_DEFINE_HPP
