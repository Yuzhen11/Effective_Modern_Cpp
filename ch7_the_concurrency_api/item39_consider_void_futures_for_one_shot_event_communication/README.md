# Item 39: Consider void future for on-shot event communication

inter-thread communication: 

## condition variable

Detecting task: detects the condition

Reacting task: reacts to the condition

The problem of direct use of condvar:

1. If the detecting task notifies the condvar before the reacting task watis, the reacting task will hang.

2. Spurious wakeups

What about using atomic?
    
    std::atomic<bool> flag(false);

    flag =  true; // tell 

    while(!flag);  // prepare to react

The thread is busy waiting, not blocked.

Combined them:

    std::condition_variable cv;
    std::mutex m;
    bool flag(false);

    // detect event
    {
        std::lock_guard<std::mutex> g(m);
        flag = true;
        cv.notify_one();
    }

    // react
    {
        std::unique_lock(std::mutex) lk(m);
        cv.wait(lk, []{ return flag; });
    }

## wait on a future

    std::promise<void> p;  // promise for communications channel

    p.set_value(); // tell

    p.get_future().wait();  // wait for future 

Problems:

1. incurs the cost of heap-based allocation and deallocation of shared state.

2. std::promise may be set only once. One-shot

## promise for thread setup

    std::promise<void> p;

    void detect() {
        auto sf = p.get_future().share();  // sf's type is std::shared_future<void>

        std::vector<std::thread> vt;

        for (int i = 0; i < threadToRun; ++ i) {
            vt.emplace_back([sf]{ sf.wait(); react(); });  // wait on local copy of sf
        }

        p.set_value();  // unsuspend all threads

        for (auto& t : vt) {
            t.join();
        }
    }

## Things to Remember

* For simple event communication, condvar-based designs require a superfluous mutex, impose constraints
on the relative progress of detecting and reacting taks, and require taks to verify that the event has taken place.

* Designs employing a flag avoid those problems, but are based on polling, not blocking.

* A condvar adn flag can be used together, but the resulting communications mechanism is somewhat stlited.

* Using std::promises and futures dodges these issues, but approach uses heap memory for shared states, and it's limited
to on-shot communication.
