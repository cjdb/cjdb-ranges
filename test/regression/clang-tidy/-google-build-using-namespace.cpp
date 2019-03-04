//
//  Copyright 2019 Christopher Di Bella
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

/// This test checks that google-build-using-namespace is *disabled*.
/// \see https://clang.llvm.org/extra/clang-tidy/checks/google-build-using-namespace.html.

#include <cstddef>
#include <iostream>
#include <string>

namespace test { inline namespace string_literals {
   std::string operator""_s(char const* str, std::size_t) { return str; }
}}   // namespace test::string_literals

int main()
{
   using namespace test::string_literals;
   auto const hello = "hello\n"_s;
   std::cout << hello;
}
