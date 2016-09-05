#include <array>

constexpr int pow(int base, int exp) noexcept {
    return (exp == 0? 1 : base*pow(base, exp-1));
}

// C++14
constexpr int pow2(int base, int exp) noexcept {
    auto result = 1;
    for (int i = 0; i < exp; ++ i) result *= base;
    return result;
}

class Point {
public:
    constexpr Point(double xVal = 0, double yVal = 0) noexcept
    : x(xVal), y(yVal)
    {}

    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }

    constexpr void setX(double newX) noexcept   // C++14
    { x = newX; }
    constexpr void setY(double newY) noexcept   // C++14
    { y = newY; }

private:
    double x,y;
};

int main() {
    // int sz;
    //
    // constexpr auto arraySize1 = sz; // error
    // std::array<int, sz> data1;  // error
    
    constexpr auto arraySize2 = 10;
    std::array<int, arraySize2> data2;

    // const cannot 
    // int sz;
    // const auto arraySize = sz;
    // std::array<int, arraySize> data; // error

    constexpr auto numConds = 5;
    std::array<int, pow(3, numConds)> results; // compile time

    auto base = 10;
    auto exp = 10;
    // ... 
    auto baseToExp = pow(base, exp); // runtime

}
