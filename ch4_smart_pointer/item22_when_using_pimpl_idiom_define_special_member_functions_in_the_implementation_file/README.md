# Item 22: When using the Pimpl idiom, define special member functions in the implementation file

The issue in this issue looks like some bugs... 

When using Pimpl Idiom and std::uniq_ptr, we should let the special member functions (destructor, copy construtor...) in class
implementation file. Otherwise, incomplete type.

## Things to Remember

* The Pimpl Idiom decrease the build times by reducing compilation dependencies between class clients and class implementation.

* For std::unique_ptr pImpl pointers, declare special member functions in class header, but implement them in the 
implementation file. Do this even if the default function implementation are acceptable.

* The above advice applies to std::unique_ptr, but not to std::shared_ptr.
