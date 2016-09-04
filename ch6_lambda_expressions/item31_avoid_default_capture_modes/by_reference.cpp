#include <iostream>
#include <vector>
#include <functional>

using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;

void addDivisorFilter() {
    auto divisor = 2;

    filters.emplace_back([&](int value) {  // danger!!! refer to divisor will dangle!
        return value % divisor == 0;
    });

    filters.emplace_back([&divisor](int value) {  // danger!!! refer to divisor will still dangle!
        return value % divisor == 0;
    });

    filters.emplace_back([=](int value) {  // now divisor won't be dangle
        return value % divisor == 0;
    });
}
int main() {
}
