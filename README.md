# cjdb-ranges

`cjdb-ranges` is a C++20 implementation for range abstractions. It prioritises the implementation
for [C++20 ranges][1] using the [clang-concepts-monorepo][2] fork of Clang, but supports both libc++
and libstdc++.

## What are 'C++20 ranges'?

The term 'C++20 ranges' is used to refer to range abstractions that can be found in standard C++20.
_Most_ of this content can be found in the [[concepts]][3], [[iterators]][4], [[ranges]][5], and
[[algorithms]][6] clauses of the C++20 specification, but a handful can be found in the
[[function.objects]][7] subclause as well.

## Installing cjdb-ranges

Please see [doc/install.md][8].

## Getting started

Please see [doc/getting-started.md][9].

[1]: #what-are
[2]: https://github.com/saarraz/clang-concepts-monorepo
[3]: http://eel.is/c++draft/algorithms
[4]: http://eel.is/c++draft/concepts
[5]: http://eel.is/c++draft/iterators
[6]: http://eel.is/c++draft/ranges
[7]: http://eel.is/c++draft/function.objects
[8]: doc/install.md
[9]: doc/getting-started.md
