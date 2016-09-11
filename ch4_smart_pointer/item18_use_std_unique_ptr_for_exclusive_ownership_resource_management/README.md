# Item 18: Use std::unique_ptr for exclusive-ownership resource management

A factory function:

    template<typename... Ts>
    std::unique_ptr<Investment, decltype(delInvmt)>
    makeInvestment(Ts&&... params) {
        std::unique_ptr<Investment, decltype(delInvmt)> pInv(nullptr, delInvmt);
        if ( /* a Stock object should be created */) {
            pInv.reset(new Stock(std::forward<Ts>(params)...));  // cannot implicitly assign a raw pointer to a smart pointer
        }
        ...
    }

    auto delInvmt = [](Investment* pInvestment) {
        makeLogEntry(pInvestment);
        delete pInvestment;
    };

When a custom deleter can be implemented as either a function or a captureless lambda expression, the lambda is preferable.

std::unique_ptr<T[]>, pointer to array.

Can be easily and efficiently convert to a std::shared_ptr:

    std::shared_ptr<Investment> sp = makeInvestment(...);  // converts std::unique_ptr to std::shared_ptr


## Things to Remember

* std::unique_ptr is a small, fast, move-only smart pointer for managing resources
with excluisve-ownership semantics.

* By default, resource destruction takes place via delete, but custom deleters can be specified.
Stateful deleters and function pointers as deleters increase the size of std::unique_ptr objects.

* Converting a std::unique_ptr to a std::shared_ptr is easy.
