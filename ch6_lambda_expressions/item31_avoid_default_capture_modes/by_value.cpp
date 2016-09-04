#include <iostream>
#include <vector>
#include <functional>

using FilterContainer = std::vector<std::function<bool(int)>>;

class Widget {
public:
    void addFilter() {
        // cannot compile
        // filters.emplace_back([=](int value) {
        //     return value % divisor == 0;  // divisor not available
        // });
        // cannot compile
        // filters.emplace_back([](int value) {
        //     return value % divisor == 0;  // divisor not available
        // });
        // cannot compile
        // filters.emplace_back([divisor](int value) {
        //     return value % divisor == 0;  // no local divisor to capture
        // });
        // This can work, but we cannot define the function as addFilter() const
        filters.emplace_back([this](int value) {
            return value % this->divisor == 0;  
        });
        // Create a local copy, definitely works
        auto divisorCopy = divisor;
        filters.emplace_back([divisorCopy](int value) {
            return value % divisorCopy == 0;  
        });

        filters.emplace_back([divisor = divisor](int value) {  // C++14
            return value % divisor == 0;  
        });
    }
private:
    int divisor;
    FilterContainer filters;
};

// test static
FilterContainer filters;
void addDivisorFilter() {
    static auto divisor = 10;
    filters.emplace_back([](int value) {  // automatically capture by reference!!!
        return value % divisor == 0;      // So avoid [=]
    });
    divisor++;
}

int main() {
}
