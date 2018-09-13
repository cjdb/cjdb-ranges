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
#ifndef CJDB_TEST_CONCEPTS_COMPARISON_VECTOR_HPP
#define CJDB_TEST_CONCEPTS_COMPARISON_VECTOR_HPP

#include <vector>

bool operator<(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
   return x.size() < y;
}

bool operator<(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
   return x < y.size();
}

bool operator>(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
   return y < x;
}

bool operator>(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
   return y < x;
}

bool operator<=(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
   return not (y < x);
}

bool operator<=(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
   return not (y < x);
}

bool operator>=(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
   return not (x < y);
}

bool operator>=(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
   return not (x < y);
}

bool operator==(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
   return x.size() == y;
}

bool operator==(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
   return y == x;
}

bool operator!=(std::vector<int> const& x, std::vector<int>::size_type const y) noexcept
{
   return not (x == y);
}

bool operator!=(std::vector<int>::size_type const x, std::vector<int> const& y) noexcept
{
   return not (y == x);
}

template<class T1, class T2>
concept weakly_sto = requires(T1 const& x, T2 const y) {
   x == y;
   x != y;

   y == x;
   y != x;

   x < y;
   x <= y;
   x >= y;
   x > y;

   y < x;
   y <= x;
   y >= x;
   y > x;
};

static_assert(weakly_sto<std::vector<int>, std::vector<int>::size_type>);

#endif // CJDB_TEST_CONCEPTS_COMPARISON_VECTOR_HPP
