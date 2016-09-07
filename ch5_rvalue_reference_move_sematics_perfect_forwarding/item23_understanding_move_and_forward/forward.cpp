#include <iostream>
#include <type_traits>

// work with reference collapsing
template<typename T>
T&& forward(tyepname std::remove_reference<T>::type& param) {
    return static_cast<T&&>(param);
}

class Widget {
};

void process(const Widget& lvalArg) {  // process lvalues
    std::cout << "lvalue" << std::endl;
}
void process(Widget&& rvalArg) {  // process rvalues
    std::cout << "rvalue" << std::endl;
}

template<typename T>
void logAndProcess(T&& param) {
    process(std::forward<T>(param));
}

int main() {
    Widget w;
    logAndProcess(w);  // call with lvalue
    logAndProcess(std::move(w));  // call with rvalue
}
