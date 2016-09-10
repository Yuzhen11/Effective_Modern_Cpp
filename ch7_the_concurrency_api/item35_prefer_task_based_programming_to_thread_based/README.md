# Item 35: Prefer task-based programming to thread-based

thread-based:

    int doAsyncWork();
    std::thread t(doAsyncWork);

task-based:

    auto fut = std::async(doAsyncWork);

Hardware threads, Software threads, and std::threads

## Thread exhaustion

Software threads are a limited resource. If you try to create more than the system can provide, a std::system_error
exception is thrown.

Even if doAsyncWork is noexcept.

    int doAsyncWork() noexcept;
    std::thread t(doAsyncWork);  // throws if no more threads are available

## oversubscription

Rescheduling of the threads, context switch, cache refresh. 

## Let std::async handle these issues

This calls shifts the thread management responsibility to the implementer of the C++ Standard Library.

std::async doesn't gurantee to create a new software thread.

## Some situations where using threads directly may be appropriate:

* You need access to the API of the underlying threading implementation. (priority, affinity) native_handle()

* You need to and are able to optimize thread usage for your application.

* You need to implement threading technology beyond the C++ concurrency API. (thread pools)

## Things to Remember

* The std::thread API offers no direct way to get return values from asynchronously run functions,
and if those functions throw, he program is terminated.

* thread-based programmming calls for manual management of thread exhaustion, oversubscription, load balancing, 
and adaption to new platform.

* Task-based programming via std::async with the default launch policy handles most of these issues for you.
