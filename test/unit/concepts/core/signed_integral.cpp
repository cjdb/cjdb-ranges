// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/signed_integral.hpp"

#include "cjdb/test/concepts/core/fundamental.hpp"

DEFINE_MODELS_CONCEPT_CHECK_FOR(signed_integral)

int main()
{
	models_signed_integral<signed char>();
	models_signed_integral<short>();
	models_signed_integral<int>();
	models_signed_integral<long>();
	models_signed_integral<long long>();

	models_signed_integral<char, std::is_signed_v<char>>();
	models_signed_integral<wchar_t, std::is_signed_v<wchar_t>>();

	models_signed_integral<bool, false>();
	models_signed_integral<char8_t, false>();
	models_signed_integral<char16_t, false>();
	models_signed_integral<char32_t, false>();
	models_signed_integral<unsigned char, false>();
	models_signed_integral<unsigned short, false>();
	models_signed_integral<unsigned int, false>();
	models_signed_integral<unsigned long, false>();
	models_signed_integral<unsigned long long, false>();

	models_signed_integral<float, false>();
	models_signed_integral<double, false>();
	models_signed_integral<long double, false>();

	struct dummy {};
	models_signed_integral<dummy, false>();
}
