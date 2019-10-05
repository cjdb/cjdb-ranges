// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef CJDB_TYPE_TRAITS_TYPE_TRAITS_HPP
#define CJDB_TYPE_TRAITS_TYPE_TRAITS_HPP

#include "cjdb/type_traits/expose_type.hpp"
#include <type_traits>
#include <utility>

namespace cjdb {
   // Helper classes
   using std::integral_constant;
   using std::bool_constant;
   using std::true_type;
   using std::false_type;

   // Primary type categories
   using std::is_void, std::is_void_v;
   using std::is_null_pointer, std::is_null_pointer_v;
   using std::is_integral, std::is_integral_v;
   using std::is_floating_point, std::is_floating_point_v;
   using std::is_array, std::is_array_v;
   using std::is_enum, std::is_enum_v;
   using std::is_union, std::is_union_v;
   using std::is_class, std::is_class_v;
   using std::is_function, std::is_function_v;
   using std::is_pointer, std::is_pointer_v;
   using std::is_lvalue_reference, std::is_lvalue_reference_v;
   using std::is_rvalue_reference, std::is_rvalue_reference_v;
   using std::is_member_object_pointer, std::is_member_object_pointer_v;
   using std::is_member_function_pointer, std::is_member_function_pointer_v;

   // Composite type categories
   using std::is_fundamental, std::is_fundamental_v;
   using std::is_arithmetic, std::is_arithmetic_v;
   using std::is_scalar, std::is_scalar_v;
   using std::is_object, std::is_object_v;
   using std::is_compound, std::is_compound_v;
   using std::is_reference, std::is_reference_v;
   using std::is_member_pointer, std::is_member_pointer_v;

   // Type properties
   using std::is_const, std::is_const_v;
   using std::is_volatile, std::is_volatile_v;
   using std::is_trivial, std::is_trivial_v;
   using std::is_trivially_copyable, std::is_trivially_copyable_v;
   using std::is_standard_layout, std::is_standard_layout_v;
   using std::has_unique_object_representations, std::has_unique_object_representations_v;
   using std::is_empty, std::is_empty_v;
   using std::is_polymorphic, std::is_polymorphic_v;
   using std::is_abstract, std::is_abstract_v;
   using std::is_final, std::is_final_v;
   using std::is_aggregate, std::is_aggregate_v;
   using std::is_signed, std::is_signed_v;
   using std::is_unsigned, std::is_unsigned_v;

   // Supported operations
   using std::is_constructible, std::is_constructible_v;
   using std::is_trivially_constructible, std::is_trivially_constructible_v;
   using std::is_nothrow_constructible, std::is_nothrow_constructible_v;

   using std::is_default_constructible, std::is_default_constructible_v;
   using std::is_trivially_default_constructible, std::is_trivially_default_constructible_v;
   using std::is_nothrow_default_constructible, std::is_nothrow_default_constructible_v;

   using std::is_copy_constructible, std::is_copy_constructible_v;
   using std::is_trivially_copy_constructible, std::is_trivially_copy_constructible_v;
   using std::is_nothrow_copy_constructible, std::is_nothrow_copy_constructible_v;

   using std::is_move_constructible, std::is_move_constructible_v;
   using std::is_trivially_move_constructible, std::is_trivially_move_constructible_v;
   using std::is_nothrow_move_constructible, std::is_nothrow_move_constructible_v;

   using std::is_assignable, std::is_assignable_v;
   using std::is_trivially_assignable, std::is_trivially_assignable_v;
   using std::is_nothrow_assignable, std::is_nothrow_assignable_v;

   using std::is_copy_assignable, std::is_copy_assignable_v;
   using std::is_trivially_copy_assignable, std::is_trivially_copy_assignable_v;
   using std::is_nothrow_copy_assignable, std::is_nothrow_copy_assignable_v;

   using std::is_move_assignable, std::is_move_assignable_v;
   using std::is_trivially_move_assignable, std::is_trivially_move_assignable_v;
   using std::is_nothrow_move_assignable, std::is_nothrow_move_assignable_v;

   using std::is_destructible, std::is_destructible_v;
   using std::is_trivially_destructible, std::is_trivially_destructible_v;
   using std::is_nothrow_destructible, std::is_nothrow_destructible_v;

   using std::has_virtual_destructor, std::has_virtual_destructor_v;

   using std::is_swappable_with, std::is_swappable_with_v;
   using std::is_swappable, std::is_swappable_v;
   using std::is_nothrow_swappable_with, std::is_nothrow_swappable_with_v;
   using std::is_nothrow_swappable, std::is_nothrow_swappable_v;

   // Property queries
   using std::alignment_of, std::alignment_of_v;
   using std::rank, std::rank_v;
   using std::extent, std::extent_v;

   // Type relationships
   using std::is_same, std::is_same_v;
   using std::is_base_of, std::is_base_of_v;
   using std::is_convertible, std::is_convertible_v;

   template<class From, class To>
   struct is_nothrow_convertible
      : bool_constant<is_convertible_v<From, To> and noexcept(To(std::declval<From>()))> {};

   template<class From, class To>
   inline constexpr auto is_nothrow_convertible_v = is_nothrow_convertible<From, To>();

   using std::is_invocable, std::is_invocable_v;
   using std::is_invocable_r, std::is_invocable_r_v;
   using std::is_nothrow_invocable, std::is_nothrow_invocable_v;
   using std::is_nothrow_invocable_r, std::is_nothrow_invocable_r_v;

   // Const-volatility specifiers
   using std::remove_cv, std::remove_cv_t;
   using std::remove_const, std::remove_const_t;
   using std::remove_volatile, std::remove_volatile_t;

   using std::add_cv, std::add_cv_t;
   using std::add_const, std::add_const_t;
   using std::add_volatile, std::add_volatile_t;

   // References
   using std::remove_reference, std::remove_reference_t;
   using std::add_lvalue_reference, std::add_lvalue_reference_t;
   using std::add_rvalue_reference, std::add_rvalue_reference_t;

   // Pointers
   using std::remove_pointer, std::remove_pointer_t;
   using std::add_pointer, std::add_pointer_t;

   // Sign modifiers
   using std::make_signed, std::make_signed_t;
   using std::make_unsigned, std::make_unsigned_t;

   // Arrays
   using std::remove_extent, std::remove_extent_t;
   using std::remove_all_extents, std::remove_all_extents_t;

   // Miscellaneous transformations
   using std::aligned_storage, std::aligned_storage_t;
   using std::aligned_union, std::aligned_union_t;
   using std::decay, std::decay_t;

   template<class T> using remove_cvref = remove_cv<remove_reference_t<T>>;
   template<class T> using remove_cvref_t = _t<remove_cvref<T>>;

   using std::enable_if, std::enable_if_t;
   using std::conditional, std::conditional_t;
   using std::underlying_type, std::underlying_type_t;
   using std::invoke_result, std::invoke_result_t;
   using std::void_t;

   // Operations on traits
   using std::conjunction, std::conjunction_v;
   using std::disjunction, std::disjunction_v;
   using std::negation, std::negation_v;
} // namespace cjdb

#endif // CJDB_TYPE_TRAITS_TYPE_TRAITS_HPP
