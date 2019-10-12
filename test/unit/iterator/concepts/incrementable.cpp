// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "cjdb/iterator/concepts/incrementable.hpp"

using cjdb::weakly_incrementable;
using cjdb::incrementable;

static_assert(weakly_incrementable<int>);
static_assert(incrementable<int>);

static_assert(weakly_incrementable<int*>);
static_assert(incrementable<int*>);

static_assert(weakly_incrementable<int**>);
static_assert(incrementable<int**>);

static_assert(not weakly_incrementable<int[]>); // NOLINT(modernize-avoid-c-arrays)
static_assert(not incrementable<int[]>); // NOLINT(modernize-avoid-c-arrays)

static_assert(not weakly_incrementable<double>);
static_assert(not incrementable<double>);

static_assert(not weakly_incrementable<int&>);
static_assert(not incrementable<int&>);

static_assert(not weakly_incrementable<int(*)()>);
static_assert(not incrementable<int(*)()>);


struct winc1 {
	using difference_type = int;
	winc1& operator++();
	void operator++(int);
};
static_assert(weakly_incrementable<winc1>);
static_assert(not incrementable<winc1>);

struct winc2 {
	using difference_type = int;
	winc2& operator++();
	winc2 operator++(int);
};
static_assert(weakly_incrementable<winc2>);
static_assert(not incrementable<winc2>);

struct winc3 {
	winc3& operator++();
	winc3 operator++(int);

	long operator-(winc3) const;
};
static_assert(weakly_incrementable<winc3>);
static_assert(not incrementable<winc3>);

struct winc4 {
	using difference_type = short;

	winc4& operator++();
	winc4 operator++(int);

	long operator-(winc4) const;
};
static_assert(weakly_incrementable<winc4>);
static_assert(not incrementable<winc4>);

struct missing_difference_type {
	missing_difference_type& operator++();
	void operator++(int);
};
static_assert(not weakly_incrementable<missing_difference_type>);
static_assert(not incrementable<missing_difference_type>);

struct floating_difference_type {
	using difference_type = float;

	floating_difference_type& operator++();
	void operator++(int);
};
static_assert(not weakly_incrementable<floating_difference_type>);
static_assert(not incrementable<floating_difference_type>);

struct non_const_minus {
	non_const_minus& operator++();
	non_const_minus operator++(int);

	long operator-(non_const_minus);
};
static_assert(not weakly_incrementable<non_const_minus>);
static_assert(not incrementable<non_const_minus>);

struct non_integral_minus {
	non_integral_minus& operator++();
	non_integral_minus operator++(int);

	void operator-(non_integral_minus);
};
static_assert(not weakly_incrementable<non_integral_minus>);
static_assert(not incrementable<non_integral_minus>);

struct bad_difference_type_good_minus {
	using difference_type = float;

	bad_difference_type_good_minus& operator++();
	void operator++(int);

	int operator-(bad_difference_type_good_minus) const;
};
static_assert(not weakly_incrementable<bad_difference_type_good_minus>);
static_assert(not incrementable<bad_difference_type_good_minus>);

struct missing_default_initializable {
	using difference_type = int;
	missing_default_initializable() = delete;

	missing_default_initializable& operator++();
	void operator++(int);
};
static_assert(not weakly_incrementable<missing_default_initializable>);
static_assert(not incrementable<missing_default_initializable>);

struct missing_movable {
	using difference_type = int;

	missing_movable() = default;
	missing_movable(missing_movable&&) = delete;

	missing_movable& operator++();
	void operator++(int);
};
static_assert(not weakly_incrementable<missing_movable>);
static_assert(not incrementable<missing_movable>);

struct missing_preinc {
	using difference_type = int;

	void operator++(int);
};
static_assert(not weakly_incrementable<missing_preinc>);
static_assert(not incrementable<missing_preinc>);

struct missing_postinc {
	using difference_type = int;

	missing_postinc& operator++();
};
static_assert(not weakly_incrementable<missing_postinc>);
static_assert(not incrementable<missing_postinc>);

struct inc1 {
	using difference_type = int;

	inc1& operator++();
	inc1 operator++(int);

	bool operator==(inc1) const;
	bool operator!=(inc1) const;
};
static_assert(weakly_incrementable<inc1>);
static_assert(incrementable<inc1>);

struct inc2 {
	inc2& operator++();
	inc2 operator++(int);

	bool operator==(inc2) const;
	bool operator!=(inc2) const;

	int operator-(inc2) const;
};
static_assert(weakly_incrementable<inc2>);
static_assert(incrementable<inc2>);

struct inc3 {
	using difference_type = int;

	inc3& operator++();
	inc3 operator++(int);

	bool operator==(inc3) const;
	bool operator!=(inc3) const;

	void operator-(inc3) const;
};
static_assert(weakly_incrementable<inc3>);
static_assert(incrementable<inc3>);

struct noncopyable1 {
	using difference_type = int;

	noncopyable1() = default;
	noncopyable1(noncopyable1&&) = default;
	noncopyable1(noncopyable1 const&) = delete;

	noncopyable1& operator=(noncopyable1&&) = default;
	noncopyable1& operator=(noncopyable1 const&) = delete;

	noncopyable1& operator++();
	noncopyable1 operator++(int);

	bool operator==(noncopyable1) const;
	bool operator!=(noncopyable1) const;
};
static_assert(weakly_incrementable<noncopyable1>);
static_assert(not incrementable<noncopyable1>);

struct noncopyable2 {
	noncopyable2() = default;
	noncopyable2(noncopyable2&&) = default;
	noncopyable2(noncopyable2 const&) = delete;

	noncopyable2& operator=(noncopyable2&&) = default;
	noncopyable2& operator=(noncopyable2 const&) = delete;

	noncopyable2& operator++();
	noncopyable2 operator++(int);

	int operator-(noncopyable2 const&) const;

	bool operator==(noncopyable2) const;
	bool operator!=(noncopyable2) const;
};
static_assert(weakly_incrementable<noncopyable2>);
static_assert(not incrementable<noncopyable2>);

struct noncopyable3 {
	using difference_type = int;

	noncopyable3() = default;
	noncopyable3(noncopyable3&&) = default;
	noncopyable3(noncopyable3 const&) = delete;

	noncopyable3& operator=(noncopyable3&&) = default;
	noncopyable3& operator=(noncopyable3 const&) = delete;

	noncopyable3& operator++();
	noncopyable3 operator++(int);

	int operator-(noncopyable3 const&) const;

	bool operator==(noncopyable3) const;
	bool operator!=(noncopyable3) const;
};
static_assert(weakly_incrementable<noncopyable3>);
static_assert(not incrementable<noncopyable3>);

int main() {}
