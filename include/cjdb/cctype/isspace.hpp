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
#ifndef CJDB_FUNCTIONAL_ISSPACE_HPP
#define CJDB_FUNCTIONAL_ISSPACE_HPP

#include "cjdb/concepts/core/character.hpp"
#include "cjdb/cctype/is_newline.hpp"

namespace cjdb {
   namespace detail_isspace_fn {
      struct isspace_fn {
         template<class CharT>
         constexpr bool operator()(CharT const c) const noexcept
         {
            return c == static_cast<CharT>(' ')  or
                   c == static_cast<CharT>('\r') or
                   c == static_cast<CharT>('\t') or
                   c == static_cast<CharT>('\v') or
                   is_newline(c);
         }
      };
   } // namespace detail_isspace_fn

   /// \brief Checks if the character is a whitespace character. Currently checks for:
   ///      * ' '  (space)
   ///      * '\f' (form-feed)
   ///      * '\n' (newline)
   ///      * '\r' (carriage return)
   ///      * '\t' (horisontal tab)
   ///      * '\v' (vertial tab)
   /// \param c The character to classify.
   /// \returns true if the character is a whitespace character; false otherwise.
   /// \note isspace is a niebloid. This means that:
   ///      * explicit template arguments may not be specified when calling isspace.
   ///      * isspace cannot be found by argument-dependent lookup (ADL).
   ///      * when isspace is found by normal unqualified lookup, it inhibits ADL.
   ///
   inline constexpr auto isspace = detail_isspace_fn::isspace_fn{};
} // namespace cjdb

#endif // CJDB_FUNCTIONAL_ISSPACE_HPP
