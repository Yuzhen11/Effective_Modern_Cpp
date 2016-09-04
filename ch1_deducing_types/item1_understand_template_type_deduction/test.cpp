#include "util.hpp"

#include <iostream>

// Case 1
// *ParamType* is a reference or pointer, but not a universal reference
// 1.1
template<typename T>
void f11(T& tmp) {
    std::cout << type_name<T>() << std::endl;
}
// 1.2
template<typename T>
void f12(const T& tmp) {
    std::cout << type_name<T>() << std::endl;
}
// 1.3
template<typename T>
void f13(T* tmp) {
    std::cout << type_name<T>() << std::endl;
}

// Case 2
// Universal Reference
template<typename T>
void f2(T&& tmp) {
    std::cout << type_name<T>() << std::endl;
}

// Case 3
// Pass by value
template<typename T>
void f3(T tmp) {
    std::cout << type_name<T>() << std::endl;
}

int main() {
    int x = 27;   // x in an int
    const int cx = x;   // cx is a const int
    const int& rx = x;  // rx is a reference to x as a const int

    // Case 1
    // *ParamType* is a reference or pointer, but not a universal reference
    // Rules: 
    // 1. Reference will be ignored
    // 2. deduce
    // 1.1
    f11(x);  // T is int
    f11(cx);  // T is const int
    f11(rx);  // T is const int

    // 1.2
    f12(x);  // T is int
    f12(cx);  // T is int
    f12(rx);  // T is int

    // 1.3
    const int* px = &x;
    f13(&x);  // T is int
    f13(px);  // T is const int

    std::cout << "-----" << std::endl;

    // Case 2
    // Universal Reference
    f2(x);  // x is int, so T is int&
    f2(cx);  // cx is const int, so T is const int&
    f2(rx);  // rx is const int&, so T is const int&
    f2(27);  // 27 is rvalue, so T is int

    std::cout << "-----" << std::endl;
    // Case 3
    // Pass by value
    f3(x);  // T is int
    f3(cx);  // T is int
    f3(rx);  // T is int
    f3(27);  // T is int
    const char* const ptr = "hello";
    f3(ptr); // T is const char*

}
