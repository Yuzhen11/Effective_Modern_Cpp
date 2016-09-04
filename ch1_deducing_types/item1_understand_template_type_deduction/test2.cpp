#include "util.hpp"

#include <iostream>

// 1.1
template<typename T>
void f11(T& tmp) {
    std::cout << type_name<T>() << std::endl;
}
// 3
template<typename T>
void f3(T tmp) {
    std::cout << type_name<T>() << std::endl;
}

template<typename T , std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept {
    return N;
}

void someFunc(int, double) {}

int main() {
    // Array Arguments
    // Decays to pointers
    const char name[] = "Hello";
    const char* ptrToName = name;
    f3(name);  // T is const char*
    f3(ptrToName); // T is const char*

    f11(name);  // T is const char[6]
    f11(ptrToName); // T is const char*

    std::cout << "-----" << std::endl;
    //create a template that deduces the number of elements that an array contains
    int keyVals[] = {1,3,5,7}; // keyVals is int* const
    std::cout << arraySize(keyVals) << std::endl;

    int mappedVals[arraySize(keyVals)];
    std::array<int, arraySize(keyVals)> mappedVals2;

    std::cout << "----" << std::endl;

    // Functions Arguments 
    // Decays to pointers
    f3(someFunc);
    f11(someFunc);
}
