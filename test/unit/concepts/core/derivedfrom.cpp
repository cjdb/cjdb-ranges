// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/concepts/core/derived_from.hpp"

struct Base1 {};
struct Derived1 : Base1 {};
struct Derived2 : Base1 {};

struct Base2 : private Base1 {};
struct Derived3 : Base2 {};

struct Base3 : protected Base2 {};
struct Derived4 : Base3 {};
struct Derived5 : Derived4 {};

int main()
{
	{ // Base1 is the subject.
		static_assert(cjdb::derived_from<Base1, Base1>);
		static_assert(not cjdb::derived_from<Base1, Base2>);
		static_assert(not cjdb::derived_from<Base1, Base3>);

		static_assert(not cjdb::derived_from<Base1, Derived1>);
		static_assert(not cjdb::derived_from<Base1, Derived2>);
		static_assert(not cjdb::derived_from<Base1, Derived3>);
		static_assert(not cjdb::derived_from<Base1, Derived4>);
	}

	{ // Derived1 is the subject.
		static_assert(cjdb::derived_from<Derived1, Base1>);
		static_assert(not cjdb::derived_from<Derived1, Base2>);
		static_assert(not cjdb::derived_from<Derived1, Base3>);

		static_assert(cjdb::derived_from<Derived1, Derived1>);
		static_assert(not cjdb::derived_from<Derived1, Derived2>);
		static_assert(not cjdb::derived_from<Derived1, Derived3>);
		static_assert(not cjdb::derived_from<Derived1, Derived4>);
	}

	{ // Derived2 is the subject.
		static_assert(cjdb::derived_from<Derived2, Base1>);
		static_assert(not cjdb::derived_from<Derived2, Base2>);
		static_assert(not cjdb::derived_from<Derived2, Base3>);

		static_assert(not cjdb::derived_from<Derived2, Derived1>);
		static_assert(    cjdb::derived_from<Derived2, Derived2>);
		static_assert(not cjdb::derived_from<Derived2, Derived3>);
		static_assert(not cjdb::derived_from<Derived2, Derived4>);
	}

	{ // Base2 is the subject.
		static_assert(not cjdb::derived_from<Base2, Base1>);
		static_assert(    cjdb::derived_from<Base2, Base2>);
		static_assert(not cjdb::derived_from<Base2, Base3>);

		static_assert(not cjdb::derived_from<Base2, Derived1>);
		static_assert(not cjdb::derived_from<Base2, Derived2>);
		static_assert(not cjdb::derived_from<Base2, Derived3>);
		static_assert(not cjdb::derived_from<Base2, Derived4>);
	}

	{ // Derived3 is the subject.
		static_assert(not cjdb::derived_from<Derived3, Base1>);
		static_assert(    cjdb::derived_from<Derived3, Base2>);
		static_assert(not cjdb::derived_from<Derived3, Base3>);

		static_assert(not cjdb::derived_from<Derived3, Derived1>);
		static_assert(not cjdb::derived_from<Derived3, Derived2>);
		static_assert(    cjdb::derived_from<Derived3, Derived3>);
		static_assert(not cjdb::derived_from<Derived3, Derived4>);
	}

	{ // Base3 is the subject.
		static_assert(not cjdb::derived_from<Base3, Base1>);
		static_assert(not cjdb::derived_from<Base3, Base2>);
		static_assert(    cjdb::derived_from<Base3, Base3>);

		static_assert(not cjdb::derived_from<Base3, Derived1>);
		static_assert(not cjdb::derived_from<Base3, Derived2>);
		static_assert(not cjdb::derived_from<Base3, Derived3>);
		static_assert(not cjdb::derived_from<Base3, Derived4>);
	}

	{ // Derived4 is the subject.
		static_assert(not cjdb::derived_from<Derived4, Base1>);
		static_assert(not cjdb::derived_from<Derived4, Base2>);
		static_assert(    cjdb::derived_from<Derived4, Base3>);

		static_assert(not cjdb::derived_from<Derived4, Derived1>);
		static_assert(not cjdb::derived_from<Derived4, Derived2>);
		static_assert(not cjdb::derived_from<Derived4, Derived3>);
		static_assert(    cjdb::derived_from<Derived4, Derived4>);
	}

	{ // Derived5 is the subject.
		static_assert(not cjdb::derived_from<Derived5, Base1>);
		static_assert(not cjdb::derived_from<Derived5, Base2>);
		static_assert(    cjdb::derived_from<Derived5, Base3>);

		static_assert(not cjdb::derived_from<Derived5, Derived1>);
		static_assert(not cjdb::derived_from<Derived5, Derived2>);
		static_assert(not cjdb::derived_from<Derived5, Derived3>);
		static_assert(    cjdb::derived_from<Derived5, Derived4>);
		static_assert(    cjdb::derived_from<Derived5, Derived5>);
	}
}
