# Item 38: Be aware of varying thread handle destructor behavior

Destruction of joinable std::thread terminate the program, because two obvious alternatives: an implicit join
and an implicit detach were considered worse choices.

The destruction for a future behaves differently. Sometimes detach, sometimes join, sometimes neither.

Shared State between future and promise.

* The destructor for the last future referring to a shared state for a non-deferred task launched via
std::async block until the task completes.

* The destructor for all other futures simply destroys the futrue object.

Somethings like reference count.

## Things to Remember

* Future destructors normally just destroy the future's data members

* The final future referring to a shared state for non-deferred task launched
via std::async blocks until the task completes.
