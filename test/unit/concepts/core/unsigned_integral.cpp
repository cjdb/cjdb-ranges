// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/unsigned_integral.hpp"

#include "cjdb/test/concepts/core/fundamental.hpp"

DEFINE_MODELS_CONCEPT_CHECK_FOR(unsigned_integral)

int main()
{
	models_unsigned_integral<bool>();
	models_unsigned_integral<char8_t>();
	models_unsigned_integral<char16_t>();
	models_unsigned_integral<char32_t>();
	models_unsigned_integral<unsigned char>();
	models_unsigned_integral<unsigned short>();
	models_unsigned_integral<unsigned int>();
	models_unsigned_integral<unsigned long>();
	models_unsigned_integral<unsigned long long>();

	models_unsigned_integral<char, std::is_unsigned_v<char>>();
	models_unsigned_integral<wchar_t, std::is_unsigned_v<wchar_t>>();

	models_unsigned_integral<signed char, false>();
	models_unsigned_integral<short, false>();
	models_unsigned_integral<int, false>();
	models_unsigned_integral<long, false>();
	models_unsigned_integral<long long, false>();

	models_unsigned_integral<float, false>();
	models_unsigned_integral<double, false>();
	models_unsigned_integral<long double, false>();

	struct dummy {};
	models_unsigned_integral<dummy, false>();
}
