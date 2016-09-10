# Item 36: Specify std::launch::async if asynchronicity is essential

## Two modes

* The std::launch::async launch policy means that f must be run asynchronously, i.e., on a different thread.

* The std::launch::deferred launch policy means that f may run only when get or wait is called on the future
returned by std::async. The execution is deferred. Synchronously.

## Default mode

Default way is to run them asynchronously or synchronously:

    auto fut1 = std::aysnc(f);
    auto fut1 = std::aysnc(std::launch::async | std::launch::deferred, f); 

* It's not possible to predict whether f will run concurrently with t. (May be scheduled or deferred)

* It's not possible to predict whether f runs on a thread different from the thread invoking get or wait on fut.

* It may not be possible to predict whether f runs at all. (May deferred)

## Cautions

1. Should work with thread_local (TLS).

2. Affect wait-based loops using timeouts, because calling wait_for or wait_until on a task that's deferred yields the value std::future_status_deferred.

## Real asynchronous

    auto fut = std::async(std::launch::async, f);

    template<typename F, typename.. Ts>
    inline
    auto
    reallyAsync(F&& f, Ts&&... params) {
        return std::async(std::launch::async, std::forward<F>(f), std:forward<Ts>(params)...);
    }

## Things to Remember

* The default launch policy for std::async permits both asynchronous and synchronous task execution.

* This flexibility leads to uncertainty when accessing thread_locals, implies that the task may never execute, and
affects program logic for timeout-based wait calls.

* Specify std::launch::async if asynchronoustask execution is essential.


