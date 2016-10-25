# Item 23: Understand std::move and std::forward

A parameter is always lvalue, even if its type is an rvalue reference!!!

    void f(Widget&& w);

w is an lvalue, even though its type is rvalue-reference-to-Widget.

std::move and std::forward are merely template functions.

std::move doesn't move anything. std::forward doesn't forward anything. At runtime, neither does anything at all. 
They generate no executable code. Not a single byte. (I think it means c++ codes but not binary?)

## std::move

std::move takes a universal reference to an object.

std::move return an rvalue reference.

If T is lvalue reference, T&& would become an lvalue_reference.
std::remove_reference is applied to T, thus ensuring that '&&' is 
applied to a type that isn't a reference.

That guarantees that std::move truly returns an rvalue reference.
rvalue references returned from functions are rvalues.

Thus, std::move casts its argument to an rvalue, and that's all it does.

Suggested name: rvalue_cast

std::move does cast! It doesn't move!

### Careful: Should not move a const variable

Before the cast, text is an lvalue const std::string and the result of the
cast is an rvalue const std::string, but throughout it all, the constness remains.

The rvalue const std::string will match the lvalue-reference-to-const ctor of std::string.

So, copy rather than move!!!

1. Don't declare objects const if you want to be able to move from them.
Move requests on const objects are silently transformed into copy operations.

2. std::move not only doesn't actually move anything, it doesn't even guarantee 
that the object it's casting will be eligible to be moved.

## std::forward

std::move unconditionally casts its argument to an rvalue, 
std::forward does it only under certain conditions. std::forward is a conditional cast.

The most common scenario is a function template taking universal reference parameter that
is to be passed to another function.

See forward.cpp

When we call logAndProcess with an lvalue, we naturally expect that lvalue
to be forwarded to process as an lvalue, and when we call logAndProcess with 
rvalue, we expect the rvalue overload of process to be invoked.

param is an lvalue. To prevent this, we use std::forward.

conditional cast: it casts to an rvalue only if its argument was initialized
with an rvalue.

## Can we replace std::move with std::forward

1. std::forward requires a template type argument.

2. the type we pass to std::forward should be a non-reference. (??)

## Things to remember

* std::move performs an unconditional cast to an rvalue. In and of itself,
it doesn't move anything.

* std::forward casts its argument to an rvalue only if that argument is bound 
to an rvalue.

* Neither std::move and std::forward do anything at runtime.
