#include <version>

#if not defined(__cpp_lib_three_way_comparison) or __cpp_lib_three_way_comparison < 201907
	#error "Your standard library does not yet have the facilities for three_way_comparable[_with]."
#endif // __cpp_lib_three_way_comparison

#include "cjdb/concepts/comparison/three_way_comparable.hpp"
