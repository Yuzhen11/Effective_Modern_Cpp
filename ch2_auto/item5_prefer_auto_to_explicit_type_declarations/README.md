# Item 5: Prefer auto to explicit type declarations

auto needs varaiable to be initialized to deduce type -> good habit

Using auto can avoid long name such as `typename std::iterator_traits<It>::value_type` ...

auto vs std::function

auto-declared holding a closure has the same type as the closure, and as such it uses only as much memory as the closure requires.

std::function may allocate heap memory to store the closure.

std::function may be bigger and slower than the auto approach!!!

In Item34, the author recommend to use lambdas instead of std::bind...

Two examples showing how auto is better

1.

    std::vector<int> v;
    uisigned sz = v.size();
    auto sz = v.size();

the code using unsigned is not portable. e.g. from 32 bits to 64 bits.

2. 

    std::unoreder_map<std::string, int> m;
    for (const std::pair<std::string, int>& p : m) {
    }
    for (const auto& p : m) {
    }

In `std::unordered_map`, the key is const, so it should be `std::pair<const std::string, int>`, first solution works by creating a temprary object!
So you cannot get p's address.

Using auto is more efficient and easier.

## Things to Remember

* auto variables must be initialized, are generally immune to type mismatches that can lead to portability or effieciency problems,
can ease the process of refactoring, and typically require less typing than variables with explicitly specified types.

* auto-typed variable are subject to the pitfalls described in Items 2 and 6.
