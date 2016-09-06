# Item 13: Prefer const_iterators to iterators

The free functions cbegin, etc are not in C++11, but C++14 rectifies this.

## Things to Remember

* prefer const_iterators to iterators.

* In maximally generic code, prefer non-member versions of begin, end, rbegin, etc.,
over their member function counterparts.
