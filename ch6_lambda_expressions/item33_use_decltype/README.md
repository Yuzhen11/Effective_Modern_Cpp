# Item 33: Use decltype on auto&& parameters to std::forward them.

C++14, generic lambdas - lambdas that use auto in their parameter specifications.

    auto f = [](auto x) {return normalize(x);};

the closure class's function call operator looks like:

    class SomeCompilerGeneratedClassName {
    public:
        template<typename T>
        auto operator()(T x) const {
            return normalize(x);
        }
    };

perfect forward x to normalize

Universal reference

    auto f = [](auto&& x) {return normalize(std::forward<???>(x);)};

If an lvalue was passed in, decltype(x) will produce a type that's an lvalue reference.
If an rvalue was passed in, decltype(x) will produce an rvalue reference type.

forward in C++14 (Item 28):
    
    template<typename T>
    T&& forward(remove_reference_t<T>& param) {
        return static_cast<T&&>(param);
    }

1. lvalue will work

2. When x is rvalue, decltype(x) is T&&, T (in forward) is rvalue reference (Widget&&) (Note: Different from Item 28, where T is Widget).

After reference collapsing, forward still work for rvalue.

    auto f = [](auto&& x) {return normalize(std::forward<decltype(x)>(x);)};

## Things to Remeber

* Use decltype on auto&& parameters to std::forward them.

