# Item 15: Use constexpr whenever possible

constexpr is very confusing...(The author said)

constexpr indicates a value that's not only constant, it's known during compilation.

Simply put, all constexpr objects are const, but not all const objects are constexpr.

* constexpr functions can be used in contexts that demand compile-time constatns.

* When constexpr funciton is called with one or more values that are not
known during compilation, it acts like normal functions, computing its result
at runtime.

In C++11, constexpr functions may contain no more than a single
executable statement: a return;

In C++14, it's free.

constexpr functions are limited to taking and returning litreal types.

User-defined types may be literal, too.

In C++14, setters can also be constexpr.

# Things to Remember

* constexpr objects are const and are initialized with values known during compilation.

* constexpr functions can produce compile-time results when called with arguments 
whose values are known during compilation.

* constexpr objects and functions may be used in a wider range of contexts than
non-constexpr objects and functions.

* constexpr is part of an object's or function;s interface.
