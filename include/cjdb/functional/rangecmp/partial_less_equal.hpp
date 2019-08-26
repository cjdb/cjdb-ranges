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
#ifndef CJDB_FUNCTIONAL_RANGECMP_PARTIAL_LESS_EQUAL_HPP
#define CJDB_FUNCTIONAL_RANGECMP_PARTIAL_LESS_EQUAL_HPP

#include "cjdb/concepts/comparison/totally_ordered.hpp"
#include "cjdb/detail/functional/rangecmp/partial_inequality.hpp"
#include "cjdb/functional/rangecmp/less_equal.hpp"

namespace cjdb::ranges {
   /// \brief Function object for performing comparisons. Applies operator<=.
   ///
   /// Unlike `less_equal`, `partial_less_equal` stores one object, and takes another as a unary
   /// argument when it is called.
   ///
   /// `partial_less_equal` is a partial function: that is, we provide a one value now, and others
   /// when the function is invoked. In keeping up with the 'you don't pay for what you don't use'
   /// idiom employed by the C++ International Standard, `partial_less_equal` only stores a value
   /// if it is constructed with an rvalue (this is to prevent issues with lifetime management).
   ///
   /// If `partial_less_equal` is constructed using an lvalue, that lvalue is _referenced_ by the
   /// partial function. Users must be careful to ensure that use of the partial function does not
   /// exceed the lifetime of the original object.
   ///
   /// \note This is an extension.
   ///
   template<totally_ordered T>
   class partial_less_equal
   : private detail_partial_inequality::partial_inequality<T, ranges::less_equal> {
   private:
      using base = detail_partial_inequality::partial_inequality<T, ranges::less_equal>;
   public:
      using base::base;
      using base::operator();
      using base::value;
      using typename base::is_transparent;
   };

   template<class T>
   partial_less_equal(T&) -> partial_less_equal<T const&>;

   template<class T>
   partial_less_equal(T&&) -> partial_less_equal<remove_const_t<remove_reference_t<T>>&&>;
} // namespace cjdb::ranges

#endif // CJDB_FUNCTIONAL_RANGECMP_PARTIAL_LESS_EQUAL_HPP
