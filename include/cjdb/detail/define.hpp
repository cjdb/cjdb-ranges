// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_DETAIL_DEFINE_HPP
#define CJDB_DETAIL_DEFINE_HPP

#define CJDB_NOEXCEPT_RETURN(...)   \
   noexcept(noexcept(__VA_ARGS__))  \
   { return __VA_ARGS__; }          \


#define CJDB_NOEXCEPT_REQUIRES_RETURN(...) \
   noexcept(noexcept(__VA_ARGS__))         \
   requires requires { __VA_ARGS__ }       \
   { return (__VA_ARGS__); }               \

#endif // CJDB_DETAIL_DEFINE_HPP
