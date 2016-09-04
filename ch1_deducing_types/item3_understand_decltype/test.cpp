#include <iostream>
#include <vector>

// 1. Ignore reference
template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i) 
    -> decltype(c[i])  {  // C++11 trailing return type
    return c[i];
}

// 2. Ignore reference
template<typename Container, typename Index>
auto authAndAccess2(Container& c, Index i)  {  // C++14
    return c[i];
}

// 3. if c[i] is reference, return a reference, however, cannot support rvalue
template<typename Container, typename Index>
decltype(auto) authAndAccess3(Container& c, Index i)  {  // C++14
    return c[i];
}

// 4. Universal reference to accept lvalue and rvalue
template<typename Container, typename Index>
decltype(auto) authAndAccess4(Container&& c, Index i)  {  // C++14
    return std::forward<Container>(c)[i];
}

// 4. Universal reference to accept lvalue and rvalue
template<typename Container, typename Index>
auto authAndAccess4(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i]){  // C++11
    return std::forward<Container>(c)[i];
}

struct Widget {};

int main() {
    std::vector<int> v = {1,2,3};
    std::cout << authAndAccess(v, 2) << std::endl;
    std::cout << authAndAccess2(v, 2) << std::endl;

    Widget w;
    const Widget& cw = w;
    auto myWidget1 = cw;   // auto type deduction: myWidget1 is Widget
    decltype(auto) myWidget2 = cw;  // decltype type deduction: myWidget2is const Widget&
}
