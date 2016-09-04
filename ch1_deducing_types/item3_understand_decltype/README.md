# Item3 Understand Decltype

Given a name or an expression, decltype tells you the name's or the expressions type.

In C++11, perhaps the primary use for decltype is declaring function templates where the
function's return type depends on its parameter types.

C++11, trailing return type

C++11 permits return types for single-statement lambdas to be deduced, and
C++14 extends this to both all lambdas and all functions, including those with
multiple statements (Even multiple returns).

In C++14, we can omit the trailing return type, leaving the leading auto.
auto does mean type deduction will take place. 

In item2, auto return type: template type deduction.
In this case, that's problematic. 

In item1, during template type deduction, the reference-ness of an initializing
expression is ignored.

    std::deque<int> d;
    authAndAccess2(d, 5);  // won't compile

To get it works, we need to use decltype type deduction for its return type.

    decltype(auto)

auto specifies that the type is to be deduced, and decltype says that decltype rules
should be used during deduction.

Now, for c[i] return a T&, authAndAccess3 return T&. For c[i] return an object, it will return an object.

Can also apply the decltype deduction rules to the initalizing expression.

Problem now: cannot pass rvalue containers to the function!

    std:deque<std:string> makeStringDeque();  // factory function
    // make copy of the 5th element of deque returned from makeStringDeque
    auto s = authAndAccess(makeStringDeque(), 5);

Solution: Universal Reference

std::forward

## Special cases for decltype

    int x = 0;
    decltype(x);  // int
    decltype((x));  // int&, expression (x) is lvalue

decltype(x) is diffferent from decltype((x)).

Pay very close attention when using decltype(auto)

## Things to Remember

* declytpe almost always yields the type of a variable or expression without any modifications.

* For lvalue expressions fo type T other than names, decltype always reports a type of T&.

* C++14 supports decltype(auto), which like auto, deduces a type from its initializer, but
it performs the type deduction using the decltype rules (reference will not be ignored).
