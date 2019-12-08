// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Defines types that will be used for testing indirectly_readable, indirectly_writable, and their
// dependants.
//
#ifndef CJDB_TEST_ITERATOR_READ_WRITE_HPP
#define CJDB_TEST_ITERATOR_READ_WRITE_HPP

namespace cjdb_test {
	struct traditional_indirection {
		using value_type = int;
		value_type& operator*() const;
	};

	struct alternative_indirection {
		using element_type = long;
		element_type& operator*() const;
	};

	struct proxy_indirection {
		using value_type = int;
		value_type operator*() const;
	};

	struct read_only_indirection {
		using value_type = int const;
		value_type& operator*() const;
	};

	struct indirection_mismatch {
		using value_type = int;
		float& operator*() const;
	};

	struct iter_move_mismatch {
		using value_type = int;
		value_type& operator*() const;

		friend float& iter_move(iter_move_mismatch&);
	};

	struct indirection_and_iter_move_mismatch {
		using value_type = int;
		float& operator*() const;

		friend unsigned long long& iter_move(indirection_and_iter_move_mismatch&);
	};

	struct missing_dereference {
		using value_type = int;
	};
} // namespace cjdb_test

#endif // CJDB_TEST_ITERATOR_READ_WRITE_HPP
