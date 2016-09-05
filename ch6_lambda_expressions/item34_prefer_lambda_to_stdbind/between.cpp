#include <functional>

int main() {
    using namespace std::placeholders;

    int lowVal = 1;
    int highVal = 10;
    auto betweenL = 
        [lowVal, highVal] (const auto& val)
        { return lowVal <= val && val <= highVal; };

    auto betweenB = 
        std::bind(std::logical_and<>(), 
                std::bind(std::less_equal<>(), lowVal, _1),
                std::bind(std::less_equal<>(), _1, highVal));
}
