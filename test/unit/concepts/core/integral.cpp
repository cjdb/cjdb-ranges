// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/integral.hpp"

#include "cjdb/test/concepts/core/fundamental.hpp"

DEFINE_MODELS_CONCEPT_CHECK_FOR(integral)

int main()
{
	models_integral<bool>();
	models_integral<wchar_t>();
	models_integral<char8_t>();
	models_integral<char16_t>();
	models_integral<char32_t>();

	models_integral<char>();
	models_integral<signed char>();
	models_integral<unsigned char>();
	models_integral<short>();
	models_integral<unsigned short>();
	models_integral<int>();
	models_integral<unsigned int>();
	models_integral<long>();
	models_integral<unsigned long>();
	models_integral<long long>();
	models_integral<unsigned long long>();

	models_integral<float, false>();
	models_integral<double, false>();
	models_integral<long double, false>();

	struct dummy {};
	models_integral<dummy, false>();
}
