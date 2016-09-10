# Familiarize yourself with perfect forwarding failure cases

    template<typename T>
    void fwd(T&& param) {
        f(std::forward<T>(param));
    }

    template<typename... Ts>
    void fwd(Ts&&... param) {
        f(std::forward<Ts>(param)...);
    }

## Braced initializers

    void f(const std::vector<int>& v);

    f({1,2,3});  // fine
    fwd({1,2,3});  // error

Type deduction fails when accepting braced initializers.

However, auto won't fail.

Workaround:
    
    auto il = {1,2,3};  // il's type deduced to std::initializer_list<int>

    fwd(il);  // fine

## 0 or NULL as null pointers

We should use nullptr.

## Declaration-only integral static cosnt and constexpr data.

For static const and constexpr, definition are not needed. So no memory are there. So cannot take address or reference.

Compiler performs const propagation...

If you want the universal reference to work, define static const and constexpr in .cpp.

## Overloading function names and template names

Should know the exact funciton type.

## Bitfields

Cannot take reference...

## Things to Remember

* Perfect forwarding fails when template type deduction fails or when it deduces the wrong type.

* The kinds of arguments that lead to perfect forwarding failure are braced initializers, null pointers expressed as 0 or NULL,
declaration-only integral const static data members, template and overload function names and bitfields.
