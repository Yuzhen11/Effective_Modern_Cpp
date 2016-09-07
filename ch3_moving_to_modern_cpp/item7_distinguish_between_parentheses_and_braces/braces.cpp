#include <iostream>
#include <atomic>

class Widget {
public:
    Widget() {
        std::cout << "Default construct" << std::endl;
    }
    Widget(const Widget& _w) {
        std::cout << "Copy construct" << std::endl;
    }
    Widget& operator=(const Widget& _w) {
        std::cout << "Copy assign" << std::endl;
    }

    Widget(int a) {
    }
};

class A {
private:
    int x {0};   // fine
    int y = 0;   // fine
    // int z(0);    // error!
};


int main() {
    {
        int x(0);
        int y = 0;
        int z{0};
        int zz = {0};
    }

    {
        Widget w1;   // default construct
        Widget w2 = w1;  // copy construct
        w1 = w2;  // copy assign
    }

    // Uniform initialization
    {
        std::atomic<int> ai1{0};  // fine
        std::atomic<int> ai2(0);  // fine
        // std::atomic<int> ai3 = 0;  // error
    }
    
    // Prohibits implicit narrowing conversions
    {
        double x, y, z;
        int sum1{x+y+x};  // error, only warnning in g++ 5.2.0
        int sum2(x+y+z);  // fine
        int sum3 = x+y+z;  // fine
    }

    // Immunity to C++'s most vexing parse
    {
        Widget w1(10);  // call Widget constructor with 10
        Widget w2();  // most vexing parse! Declare a function!!!
        Widget w3{};  // call Wiget ctor with no args
    }

}
