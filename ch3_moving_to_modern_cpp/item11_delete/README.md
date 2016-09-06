# Prefer deleted functions to private undefined ones

## delete special member functions

The C++98 approach to preventing use of functions (copy operations) is to declare them private and not define them.

friends invoke them will fail in linking phase.

In C++11, a better way is to make them `= delete`.

## delete any function

any function may be deleted.

    bool isLuck(int number);
    bool isluck(char) = delete;  // reject chars
    bool isluck(bool) = delete;  // reject bools 

## Prevent use of template instantiations that should be disables

    template<typename T>
    void processPointer(T* ptr);

    template<>
    void processPointer(void*) = delete;

    template<>
    void processPointer(char*) = delete;

Template specializations must be written at namespace scope, not class scope.

Delete them in namespace.

## Things to Remember

* Prefer deleted functions to private undefined ones.

* Any function may be deleted, including non-member functions and template instantiations.
