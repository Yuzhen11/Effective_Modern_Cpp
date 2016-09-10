# Item 37: Make std::thread unjoinable on all paths

## Unjoinable

* Default-constructed std::threads

* std::thread objects that have been moved from

* std::threads that have been joined

* std::threads that have been detached

## When the destructor of std::thread is called if the thread is joinable, the program terminates.

Why?

* An implicit join: Need to wait...

* An implicit detach: Use resources and may modify wrong memory!

So, the committee chooses to let the program terminate...

## ThreadRAII (Resource Acquisition Is Initialization)

Design a class to do implicit join or detach...

    class ThreadRAII {
    public:
        enum class DtorAction { join, detach};

        ThreadRAII(std::thread&& t, DtorAction a)
        :action(a), t(std::move(t)) {}

        ~ThreadRAII() {
            if (t.joinable()) {  // may become unjoinable outside
                if (action == DtorAction::join) 
                    t.join();
                else
                    t.detach();
            }
        }

        ThreadRAII(ThreadRAII&&) = default;
        ThreadRAII& operator=(ThreadRAII&&) = default;

        std::thread& get() {return t;}  // Similar API as shared_ptr
    private:
        DtorAction action;
        std::thread t;  // Good to define thread in the last, to make everything ready in construction before create the thread object
    };

## Things to Remember

* Make std::threads joinable on all paths

* join-on-destruction can lead to difficult-to-debug performance anomalies.

* detach-on-destruction can lead to difficult-to-debug undefined behavior.

* Declare std::thread objects last in lists of data members.
