# Item 32: Use init capture to move objects into closures

Sometimes we want to have a move-only object (std::uniq_ptr or a std::future) to get into a closure. 
C++11 offers no way to do it. C++14 does.

init capture make it possible for you to specify:

1. the name of a data member in the closure class generated from lambda and

2. an expression initializing that data member.

    auto func = [pw = std::move(pw)] {};

How to do this in C++11?

1. Use a class member to store init object.

2. std:bind

1. moving the object to be captured into a function object produced by std::bind and

2. giving the lambda a reference to the "captured" object.

## Things to remeber

* Use C++14's init capture to move objects into closures.

* In C++11, emulate init capture via hand-written classes or std::bind.
