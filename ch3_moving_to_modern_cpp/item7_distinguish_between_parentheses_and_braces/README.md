# Item7: Distinguish between () and {} when creating objects.

As a general rule, initialization values may be specified with parenthese, and equals sign, or braces:

    int x(0);
    int y = 0;
    int z{0};
    int zz = {0};

Distinguish initialization from assignment. Different function calls are invovled.

    Widget w1;   // default construct
    Widget w2 = w1;  // copy construct
    w1 = w2;  // copy assign

## Uniform initialization

1. Cannot initialize using parentheses in class

    class A {
    private:
        int x {0};   // fine
        int y = 0;   // fine
        int z(0);    // error!
    };

2. Cannot use assignment in uncopyable objects

    std::atomic<int> ai1{0};  // fine
    std::atomic<int> ai2(0);  // fine
    std::atomic<int> ai3 = 0;  // error

## Prohibits implicit narrowing conversions

    double x, y, z;
    int sum1{x+y+x};  // error, only warnning in g++ 5.2.0
    int sum2(x+y+z);  // fine
    int sum3 = x+y+z;  // fine

## Immunity to C++'s most vexing parse

    Widget w1(10);  // call Widget constructor with 10
    Widget w2();  // most vexing parse! Declare a function!!!
    Widget w3{};  // call Wiget ctor with no args

## Drawback: with std::initializer_list

See initializer_list.cpp

## Things to Remember

* Braced initialization is the most widely usable initialization syntax, it prevents
narrowing conversions, and it's immune to C++'s most vexing parse.

* During constructor overload resolution, braced initializers are matched to std::initializer_list 
parameters if at all possible, even if other constuctors offer seemingly better matches.

* An example of where the choice between parentheses and braces can make a significanse differece
is creating a std::vector<numeric type> with two arguments.

* Choosing between parentheses and braces for object creation inside templates can be challenging.

