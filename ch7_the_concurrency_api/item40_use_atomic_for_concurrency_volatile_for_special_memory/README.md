# Item 40: Use std::atomic for concurrency, volatile for special memory
    
    std::atomic<bool> valAvailable(false);

    auto imptValue = computeImportantValue();

    valAvailable = true;  // tell other tasks it's available

    // The form is like this:
    a = b;
    x = y;

std::atomic imposes restriction on how code can be reordered. Compiler must retain the order.

For volatile, the compiler can reorder the codes.

    volatile int x;
    auto y = x;
    y = x;

    x = 10;
    x = 20;

For volatile, compiler won't optimize these codes.

They can be used together...

    volatile std::atomic<int> vai;  // operations on vai are atomic and can't be optimized away
    

## Things to Remember

* std::atomic is for data accessed from multiple threads without using mutexes. It's a tool
for writing concurrent software.

* volatile is for memory where reads and writes should not be optimized away.
It's a tool for working with special memory.
