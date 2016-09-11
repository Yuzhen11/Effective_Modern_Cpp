# Item 20: Use std::weak_ptr for std::shared_ptr-like pointers that can dangle

    auto spw = std::make_shared<Widget>();  // ref count is 1

    std::weak_ptr<Widget> wpw(spw);  // ref count is still 1

    spw = nullptr;  // ref count is 0 and the Widget is destroyed

    if (wpw.expired()) .. // if wpw doesn't point to an object...

Create std::shared_ptr from std::weak_ptr.

    std::shared_ptr<Widget> spw1 = wpw.lock();  // if wpw's expired, spw1 is null

    auto spw2 = wpw.lock();  // same as above, but use auto

    std::shared_ptr<Widget> spw3(wpw);  // if wpw's expired, throw std::bad_weak_ptr


## Usage of std::weak_ptr

### Caching

    std::unique_ptr<const Widget> loadWidget(WidgetID id);

    std::shared_ptr<const Widget> fastLoadWidget(widget id) {
        static std::unorederd_map<WidgetID, std::weak_ptr<const Widget>> cache;

        auto objPtr = cache[id].lock();  // objPtr is std::shared_ptr to cached object (or null if object's not in cache)

        if (!objPtr) {  // if not in cache
            objPtr = loadWidget(id); // load it
            cache[id] = objPtr;  // cache it
        }
        return objPtr;
    }

### Observer design pattern

Subject contains a data member holding pointers to its observers. That makes it easy for subjects to issue state change notifications.
Subjects have no interest in controling the lifetime of their observers, but they have a great interest in making sure
that if an observer gets destroyed.

A resonable design is to use std::weak_ptrs to its observers.

## Prevention of std::shared_ptr cycles

Sometimes, there are cycles in pointer relationships.

## Things to Remember

* Use std::wear_ptr for std::shared_ptr-like pointers that can dangle.

* Potential use cases for std::weak_ptr include caching, observer lists, and the prevention of std::shared_ptr cycles.
