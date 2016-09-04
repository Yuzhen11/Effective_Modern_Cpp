# Item 2: Understand auto type deduction

auto type deduction is template type deduction.

Function template:

    template<typename T>
    void f(ParamType param);
    
a call:
    
    f(expr);

auto plays the role of T in the template, and the type specifier for the variable acts as ParamType.

Three cases:

* Case 1: The type specifier is a pointer or reference,  but not a universal reference.

* Case 2: The type specifier is a universal reference.

* Case 3: The type specifier is neither a pointer nor a reference.

auto type deduction works like template type deduction.


Only exception is std::initializer_list.

    auto x = {11, 23, 9};  // x is std::initializer_list<int>

    template<typename T>
    void f(T param);

    f({11, 23, 9});  // error! can't deduce type for T

A classic mistake in C++11 programming is accidentally declaring a std::initializer_list variable.

In C++14, return auto employ template type deduction, not auto type deduction. So returning a braced initializer won't compile.

    auto createInitList() {
        return {1,2,3};  // error, can't deduce type
    }

The same is true when auto is used in a parameter type specification in a C++14 lambda:

    std::vector<int> v;
    auto resetV = [&v](const auto& newValue) {v = newValue;}  // C++14
    resetV({1,2,3}); // error

## Things to remeber

* auto type deduction is usually the same as template type deduction, but auto type deduction assumes that a braced initializer 
represents a std::initializer_list, and template type deduction doesn't.

* auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.


