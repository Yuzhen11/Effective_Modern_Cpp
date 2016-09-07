# Item 9: Prefer alias declaration to typedefs

## Using alias may be easier

    typedef void (*FP)(int, const std::string&);  // typedef
    using FP = void (*)(int, const std::string&); // alias declaration

## alias with template

    template<typename T>
    using MyAllocList = std::list<T, MyAlloc<T>>;

See the alias.cpp.

The names of dependent types must be preceded by typename.
Don't know whether MyAllocList2<T>::type is a data member.

Using alias template (using), this need for typename vanished.

## type_traits

    std::remove_const<T>::type  // const T -> T
    std::remove_reference<T>::type  // T& and T&& -> T
    std::add_lvalue_reference<T>::type // T -> T&

    std::remove_const_t<T> // c++14

Implementation

    template<class T>
    using remove_const_t = typename remove_const<T>::type;

## Things to Remember

* typedef don't support templatization, but alias declarations do.

* Alias template avoid the ::type suffix and, in templates, the "typename"
prefix often required to refer to typedefs.

* C++14 offers alias templates for all the C++11 type traits transfromation.

