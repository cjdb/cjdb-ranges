// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifdef CJDB_DETAIL_DEFINE_HPP
   #undef CJDB_DETAIL_DEFINE_HPP
#else
   #error "\"cjdb/detail/undef.hpp\" can only be included in a context where "
          "\"cjdb/detail/define.hpp\" has already been included."
#endif // CJDB_DETAIL_DEFINE_HPP

#ifdef CJDB_NOEXCEPT_RETURN
   #undef CJDB_NOEXCEPT_RETURN
#endif // CJDB_NOEXCEPT_RETURN

#ifdef CJDB_NOEXCEPT_REQUIRES_RETURN
   #undef CJDB_NOEXCEPT_REQUIRES_RETURN
#endif // CJDB_NOEXCEPT_REQUIRES_RETURN
