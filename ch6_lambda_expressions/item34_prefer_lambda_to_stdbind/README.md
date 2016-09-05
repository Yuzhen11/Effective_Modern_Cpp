# Item 34: Prefer lambdas to std::bind

In C++14, there are no resonable usecases for std::bind. 


Three examples:

1. Statements are executed when the std::bind is called (test.cpp)

2. Make inline less likely to happen (overload.cpp)

3. Sometimes much simpler (between.cpp)

4. Easy to tell how to pass parameters (compress.cpp)

In C++11, however, std::bind can be justified in two constrained situtatoins:

1. Move capture (Item 32)

2. Polymorphic function objects (polymorphic_function_object.cpp)

## Things to Remember

* Lambdas are more readable, more expressive, and may be more efficient than using std::bind.

* In C++11 only, std::bind may be useful for implementing move capture or for binding objects with templatized function call operators.
