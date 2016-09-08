#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

class Widget {
public:
    int a = 10;
};

template<typename T>
void f1(std::vector<T>&& param) {  // rvalue reference
}

template<typename T>
void f2(T&& param) {  // universal reference
}

template<typename T>
void f3(const T&& param) {  // param is an rvalue reference
}

Widget func() {
    Widget w;
    w.a = 20;
    return w;
}


int main() {
    Widget&& var1 = Widget(); // rvalue reference
    var1 = func(); // rvalue reference
    auto&& var2 = var1;  // universal reference
    std::cout << &var1 << std::endl;
    std::cout << var2.a << std::endl;
    std::cout << &var2 << std::endl;

    Widget w;
    f2(w);  // lvalue passed to f; param's type is Widget&, i.e., lvalue reference
    f2(std::move(w));  // rvalue passed to f; param type is Widget&&, i.e., rvalue reference

    std::vector<int> v;
    // f1(v); // error, can't bind lvalue to rvalue reference
    
    // C++14
    auto timeFuncInvocation = 
      [] (auto&& func, auto&&... params) {
          using namespace std::chrono;
          auto start = steady_clock::now();
          // See Item 33
          std::forward<decltype(func)>(func)(
            std::forward<decltype(params)>(params)...
          );
          auto end = steady_clock::now();
          std::cout << duration_cast<duration<double>>(end-start).count() << " seconds" << std::endl;
      };
    timeFuncInvocation([](){
        std::this_thread::sleep_for(std::chrono::seconds(1));    
    });

}
