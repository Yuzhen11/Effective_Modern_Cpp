#include <iostream>
#include <vector>
#include <initializer_list>

class Widget {
public:
    Widget(int i, bool b) {
        std::cout << "int, bool constructor" << std::endl;
    }

    Widget(int i, double d) {
        std::cout << "int, double constructor" << std::endl;
    }
};

class Widget2 {
public:
    Widget2(int i, bool b) {
        std::cout << "int, bool constructor" << std::endl;
    }

    Widget2(int i, double d) {
        std::cout << "int, double constructor" << std::endl;
    }

    Widget2(std::initializer_list<long double> il) { //  constructor with initializer list
        std::cout << "initializer_list constructor" << std::endl;
    }
};

class Widget3 {
public:
    Widget3(int i, bool b) {
        std::cout << "int, bool constructor" << std::endl;
    }

    Widget3(int i, double d) {
        std::cout << "int, double constructor" << std::endl;
    }

    Widget3(std::initializer_list<bool> il) { //  constructor with initializer list
        std::cout << "initializer_list constructor" << std::endl;
    }
};

class Widget4 {
public:
    Widget4() = default;
    Widget4(int i, bool b) {
        std::cout << "int, bool constructor" << std::endl;
    }

    Widget4(int i, double d) {
        std::cout << "int, double constructor" << std::endl;
    }

    Widget4(std::initializer_list<std::string> il) { //  constructor with initializer list
        std::cout << "initializer_list constructor" << std::endl;
    }
};

template<typename T, typename... Ts>
void doSomeWork(Ts&&... params) {
    T localObject(std::forward<Ts>(params)...);  // using parens
    T localObject2{std::forward<Ts>(params)...};  // using braces
}

int main() {
    {
        Widget w1(10, true);
        Widget w2{10, true};
    }

    {
        Widget2 w3(10, true);
        Widget2 w4{10, true};  // std::initializer_list constructor invoked
    }

    {
        Widget3 w1(10, true);
        // Widget3 w2{10, 5.0};  // error, requires narrowing conversions
    }
    {
        Widget4 w1(10, true);
        Widget4 w2{10, true};  // no explicit conversion, call first ctor
    }
    {
        Widget4 w1;  // cal default ctor
        Widget4 w2{};  // call default ctor
        Widget4 w3(); // most vexing parse
        Widget4 w4({});  // call std::initializer_list ctor
        Widget4 w5{{}};  // call std::initializer_list ctor
    }
    {
        std::vector<int> v1(10, 20);  // 10 elements each is 20
        std::vector<int> v2{10, 20};  // {10, 20}
    }
    {
        // The implementation of doSomeWork really matters, parens or braces?
        doSomeWork<std::vector<int>>(10,20);
    }
}
