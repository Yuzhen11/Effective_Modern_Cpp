# Item 19: Use std::shared_ptr for shared-ownership resource management

## Reference count has performance implications:

* std::shared_ptrs are twice the size of a raw pointer.

* Memory for the reference count must be dynamically allocated.

* Increments and decrements of the reference count must be atomic.

## For std::unique_ptr, the type of deleter is part of the type of the smart pointer. std::shared_ptr is not.

    auto loggingDel = [](Widget* pw) {
        makeLogEntry(pw);
        delete pw;
    };
    std::unique_ptr<Widget, Decltype(loggingDel)> upw(new Widget, loggingDel);
    std::shared_ptr<Widget> spw(new Widget, loggingDel);

    // So they can put into the same container
    auto customDeleter1 = [](Widget* pw) {...}
    auto customDeleter2 = [](Widget* pw) {...}

    std::shared_ptr<Widget> pw1(new Widget, customDeleter1);
    std::shared_ptr<Widget> pw2(new Widget, customDeleter2);
    std::vector<std::shared_ptr<Widget>> vpw{ pw1, pw2 };

## Rules of creating control block

* std::make_shared always creates control block

* A control block is created when a std::shared_ptr is constructed from a unique-ownership pointer.

* When a std::shared_ptr constructor is called with a raw pointer, it creates a control block.

    auto pw = new Widget;

    std::shared_ptr<Widget> spw1(pw, loggingDel);  // create control block for *pw

    // May delete pw twice!!! Don't do this
    std::shared_ptr<Widget> spw2(pw, loggingDel);  // create another control block!!!

    std::shared_ptr<Widget> spw2(spw1); // Use the same control block!

std::enable_shared_from_this<T> may not be frequently used... So omit it.


## Things to Remember

* std::shared_ptr offer convenience approaching that of garbage collection for the 
shared liftime management of arbitrary resources.

* Compared to std::unique_ptr, std::shared_ptr objects are typically twice as big, incur overhead for control blocks,
and require atomic reference count manipulations.

* Defalut resource destruction is via delete, but custom deleters are supported. The type of the deleter has no effect on the 
type of the std::shared_ptr.

* Avoid creating std::shared_ptrs from variables of raw pointer type.

