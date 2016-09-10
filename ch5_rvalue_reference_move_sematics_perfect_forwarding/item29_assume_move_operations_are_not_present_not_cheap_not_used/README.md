# Item 29: Assume that move operations are not present, not cheap, and not used.


Moving std::vector is constant time.

But, moving std::array is linear time.

SSO: Small string optimization. small strings are stored in a buffer within std::string object. no heap-allocated storage is used.

several scenarios in which C++11's move sematics do you no good:

1. No move operations: the object fails to offer move operation. Actually copying..

2. Move not faster: move is not faster than copy (std::array, SSO string).

3. Move not usable: The context in which the moving would take place requires a move
operation that emits no exceptions, but that operation isn't declared noexcept. (Item 14)

## Things to Remember

* Assume that move operations are not present, not cheap, and not used.

* In code with known types or support for move sematics, there is no need for assumptions.


