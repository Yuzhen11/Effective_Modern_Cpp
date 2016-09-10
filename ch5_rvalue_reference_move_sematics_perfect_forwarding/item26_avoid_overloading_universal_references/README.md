# Avoid overloading on universal references

## Universal reference overload may be a better match...

Functions taking universal references are the greediest functions in C++.

## perfect forwarding constructors

For non-const lvalue, perfect forwarding constructor is a better match.

## perfect forwarding ctors are matched when Derived class calls to base class copy and move ctors

## Things to Remember

* Overloading on universal references almost always leads to the universal reference
overload being called more frequently than expected.

* Perfect-forwarding constructors are especially problematic, because they're
typically better matches than copy constructors fro non-const lvalue, and
they can hijack derived class to calls to bas class copy and move constructors.
