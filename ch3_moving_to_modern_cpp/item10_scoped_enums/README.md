# Item 10: Prefer scoped enums to unscoped enums

## Protect the namespace 

In C++98, the unscoped enums pollute the namespace.

    enum Color {black, white, red};  // black, white, red are in same scope as Color
    auto white = false;  // error! white already declared in this scope

In C++11, scoped enums don't leak names in this way.

    enum class Color {black, white, red}; // scoped to Color
    auto white = false;  // fine, no other

## Strongly typed

unscoped enums implicitly convert to integral types

scoped enums won't.

## Can be forward-declared

Every enum in C++ has an integral underlying type.

Adding a new status value will cause the entire system to be recompiled.

In C++11, scoped enum can be forward-declared. 

By default, the underlying type for scoped enums is int.
In C++98, no default underlying type for enum.

Can also override:
    
    enum class Status: std::uint32_t;

## Where we still need unscopted enums

std::tuple!

See the cpp for details.

## Things to Remember

* C++98-style enums are now known as unscoped enums.

* Enumerators of scoped enums are visible only within enum.
They convert to other types only with a cast.

* Both scoped and unscoped enums support specification of underlying type.
The default underlying type for scoepd enums is int. Unscoped enums have 
no default underlying type.

* Scoped enums may always be forward-declared. 
Unscoped enums may be forward declared only if their declaration specifies
an underlying type.
