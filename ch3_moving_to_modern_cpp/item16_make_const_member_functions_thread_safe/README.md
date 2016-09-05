# Item 16: Make const member functions thread safe

Thread-safe problem may exist in const member function.

Us mutex!

std::mutex can neither ne copied nor moved.

However, in some situations, a mutex is overkill.

Like std::mutexe, std::atmoic is uncopyable and unmovable.

std::atomic

For single variable or memory location requiring synchronization, 
std::atomic is adequate. But once you get to two or more variables or memroy
locations that require manipulation as a unit, you should reach for a mutex.

## Things to Remember

* Make const member functions thread safe unless you're certain they'll
never be used in a concurrent context.

* Use of std::atomic variables may offer better performance than a mutex, but
they're suited for manipulation of only a single variable or memory location.
