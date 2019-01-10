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
#ifndef CJDB_FUNCTIONAL_ISDIGIT_HPP
#define CJDB_FUNCTIONAL_ISDIGIT_HPP

#include "cjdb/concepts/core/character.hpp"
#include <cctype>

namespace cjdb {
   namespace detail_isdigit_fn {
      struct isdigit_fn {
         template<Character CharT>
         constexpr bool operator()(CharT const c) const noexcept
         {
            return std::isdigit(c);
         }
      };
   } // namespace detail_isdigit_fn

   /// \brief Checks if the character is a digit character.
   /// \param c The character to classify.
   /// \returns true if the character is a digit character; false otherwise.
   /// \note isdigit is a niebloid. This means that:
   ///      * explicit template arguments may not be specified when calling isdigit.
   ///      * isdigit cannot be found by argument-dependent lookup (ADL).
   ///      * when isdigit is found by normal unqualified lookup, it inhibits ADL.
   ///
   inline constexpr auto isdigit = detail_isdigit_fn::isdigit_fn{};
} // namespace cjdb

#endif // CJDB_FUNCTIONAL_ISDIGIT_HPP
