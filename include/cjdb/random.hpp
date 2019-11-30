// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_RANDOM_HPP
#define CJDB_RANDOM_HPP

#include "cjdb/concepts/core/same_as.hpp"
#include "cjdb/concepts/core/unsigned_integral.hpp"
#include "cjdb/concepts/callable/invocable.hpp"
#include <functional>
#include <random>

namespace cjdb {
   /// Let g be an object of type G. UniformRandomBitGenerator<G> is satisfied only if
   ///    1. Both `G::min()` and `G::max()` are constant expressions.
   ///    2. `G::min() < G::max()`.
   ///    3. `G::min() <= g()`.
   ///    4. `g() <= G::max()`.
   ///    5. `g()` has amortized constant complexity.
   ///
   /// \see [rand.req.urng]
   ///
   template <class G>
   concept uniform_random_bit_generator =
      invocable<G&> and
      unsigned_integral<std::invoke_result_t<G&>> and
      requires {
         G::min(); requires same_as<decltype(G::min()), std::invoke_result_t<G&>>;
         G::max(); requires same_as<decltype(G::max()), std::invoke_result_t<G&>>;
      };
} // namespace cjdb

#endif // CJDB_RANDOM_HPP
