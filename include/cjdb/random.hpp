//
//  Copyright Christopher Di Bella
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef CJDB_RANDOM_HPP
#define CJDB_RANDOM_HPP

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
      unsigned_integral<invoke_result_t<G&>> and
      requires {
         G::min(); requires same_as<decltype(G::min()), invoke_result_t<G&>>;
         G::max(); requires same_as<decltype(G::max()), invoke_result_t<G&>>;
      };
} // namespace cjdb

#endif // CJDB_RANDOM_HPP
