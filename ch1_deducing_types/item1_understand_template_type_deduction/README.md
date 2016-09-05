
# Item 1: Understand template type deduction

Type deduction for templates is the basis for `auto`.

Function template:

    template<typename T>
    void f(ParamType param);
    
a call:
    
    f(expr);

During compilation, compilers use *expr* to deduce *T* and *ParamType*.

Use type_name<T>() function to print the type name. The code is in
`util.hpp`, copied from stackoverflow... The `typeid(a).name()` can
not work for `const`.

## Three cases

### Case 1: *ParamType* is a reference or pointer, but not a universal reference

Rules:

1. If *expr*'s type is a reference, ignore the reference part.

2. Then pattern-match *expr*'s type against *ParamType* to determine *T*.

### Case 2: *ParamType* is a Universal Reference

Universal Reference behaves differently for lvalue and rvalue.

Rules:

1. If *expr* is an lvalue, both *T* and *ParamType* is deduced to be lvalue references.

Unusual.

Only situation in template type deduction where T is deduced to be a reference.

2. If *expr* is an rvalue, the normal (case 1) rules apply.

### Case 3: *ParamType* is neither a pointer nor a reference

Pass by value!

Rules:

1. If *expr* is a reference, ignore the reference part

2. Ignore const, volatile

Caution: const is ignored only for by-value parameters. Pointer to const is preserved.
e.g. const char\* const -> const char\*


## Things to Remember
* During template type deduction, arguments that are references are treated as 
non-references, i.e., their reference-ness is ignored.

* When deducing types for universal reference parameters, lvalue arguments get special treatment.

* When deducing types for by-value parameters, const, volatile are treaded as non-const and non-volatile.

* During template type deduction, arguments that are array or function names decay to pointers, unless they're used to iniitalize references.
