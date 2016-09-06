# Item 14: Declare functions noexcept if they won't emit exceptions

    int f(int x) throw();  // no exceptions from f: C++98 style
    int f(int x) noexcept; // no exceptions from f: C++11 style

In noexcept function, optimizers need not keepthe runtime stack in an unwindable state if an exception would propagate out of the function.

    RetType function(params) noexcept; // most optimizable
    RetType function(params) throw();  // less optimizable
    RetType function(params);          // less optimizable

## noexcept move

In C++11, std::vector::push_back can use move to optimize when current capacity is full (moving the elements to another place). 
However, what if when moving, an exception happens?

*move if you can, but copy if you must*

Use move operations in C++11 only if the move operations are known to not emit exceptions!

std::move_if_noexcept

## Conditionally noexcept

Whether they are noexcept d3epends on whetehr the expressions inside the noexcept clauses are noexcept.

    template<class T1, class T2>
    struct pair {
        ...
        void swap(pair& p) noexcept(noexcept(swap(first, p.first)) && noexcept(swap(second, p.second)));
    };

## Exception-neutral

Some functions throw no exceptions themselves, but functions they call might emit one.

## Things to Remember

* noexcept is part of a function's interface, and that means that callers may depend on it.

* noexcept functions are more optimizable than non-except functions.

* noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.

* Most functions are exception-neutral rather than noexcept.

