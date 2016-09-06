# Declare overriding functions override

For overriding to occur, serveral requirments must be met:

* the base class function must be virtual.

* The base and derived function names must be identical (except in the case of destructor).

* The parameter types of the base and derived functions must be identical.

* The constness of the base and derived functions must be identical.

* The return types and exception specifications of the base and derived functions must be compatible.

C++11 with one more:

* The functions' reference qualifiers must be identical.

    void doWork() &; // this version of doWork applies when *this is an lvalue
    void doWork() &&; // this version of doWork applies when *this is an rvalue

All these requirements for overriding mean that small mistakes can make a big difference.

*Declare it override*

    void doSomething(Widget& w); // accepts only lvalue Widgets
    void doSomething(Widget&& w); // accepts only rvalue Widgets

Member function reference qualifiers simply make it possible to draw the same distinction.

The need for reference-qualified member functions is not common, but it can arise.
See reference_qualified.cpp

## Things to Remember

* Declare overriding functions *override*.

* Mmeber function reference qualifiers make it possible to treat lvalue and rvalue object differently.
