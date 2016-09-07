# Item 8: Prefer nullptr to 0 and NULL

In C++, 0 is int, and NULL is the same.

## avoid misuse function

They don't have pointer type.

    void f(int);
    void f(bool);
    void f(void*);

    f(0);  // calls f(int), not f(void*)
    f(NULL);  // Might not compile, but typically calls f(int), not f(void*)

C++98: Avoid overloading on pointer and integral types.

nullptr has type std::nullptr_t. They type std::nullptr_t implicitly converts to all raw pointer types.
    
    f(nullptr);  // calls f(void*) overload

## nullptr is more clear

    // not clear whether result is pointer
    auto result = findRecord(...);
    if (result == 0) {
        ...
    }

    // result is a pointer
    if (result == nullptr) {
    }

## Pass 0 and NULL to a template function may not work

0 and NULL in template function may be deduced as type int, so may not be used further.

## Things to Remember

* Prefer nulltpr to 0 and NULL.

* Avoid overloading integral and pointer types.
