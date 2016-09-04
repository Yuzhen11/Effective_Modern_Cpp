# Item 4:  Know how to view deduced types

## IDE Editors

## Compiler Diagnostics

lead to compilation problems

    template<typename T>
    class TD;

## Runtime Output

typeid(x).name() is not reliable!

Passed to a template function as a by-value parameters, so reference is ignored, const/volatile is ignored.

Boost TypeIndex library is designed to succeed.

## Things to Remember

* Deduced types can often be seen using IDE editors, compiler error messages and the Boost TypeIndex library.

* The results of some tools may be neither helpful nor accuate,
so an understanding of C++'s type deduction rules remains essential.
 
