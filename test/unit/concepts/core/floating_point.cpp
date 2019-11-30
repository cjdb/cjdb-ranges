// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/floating_point.hpp"

#include "cjdb/test/concepts/core/fundamental.hpp"

DEFINE_MODELS_CONCEPT_CHECK_FOR(floating_point)

int main()
{
	models_floating_point<float>();
	models_floating_point<double>();
	models_floating_point<long double>();

	models_floating_point<bool, false>();
	models_floating_point<wchar_t, false>();
	models_floating_point<char8_t, false>();
	models_floating_point<char16_t, false>();
	models_floating_point<char32_t, false>();
	models_floating_point<char, false>();
	models_floating_point<signed char, false>();
	models_floating_point<unsigned char, false>();
	models_floating_point<short, false>();
	models_floating_point<unsigned short, false>();
	models_floating_point<int, false>();
	models_floating_point<unsigned int, false>();
	models_floating_point<long, false>();
	models_floating_point<unsigned long, false>();
	models_floating_point<long long, false>();
	models_floating_point<unsigned long long, false>();

	struct dummy {};
	models_floating_point<dummy, false>();
}
