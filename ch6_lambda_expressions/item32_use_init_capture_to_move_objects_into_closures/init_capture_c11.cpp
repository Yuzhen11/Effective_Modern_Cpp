#include <memory>
#include <iostream>
#include <vector>

class Widget {
public:
private:
};

// 1.
class IsValAndArch {
public:
    using DataType = std::unique_ptr<Widget>;

    explicit IsValAndArch(DataType&& ptr):pw(std::move(ptr)) {}

    bool operator()() const {
    }
private:
    DataType pw;
};

int main() {
    auto func = IsValAndArch(std::make_unique<Widget>());

    std::vector<double> data;

    auto func1 = [data = std::move(data)] {};  // C++ 14

    // C++11 emulation of init capture
    auto func2 = 
        std::bind(
            [](const std::vector<double>& data){},
            std::move(data));

    // C++11 emulation of init capture for mutable lambda
    auto func3 = 
        std::bind(
            [](std::vector<double>& data) mutable {},
            std::move(data));
}

