#include <boost/type_index.hpp>

#include <iostream>

template<typename T>
void f(const T& param) {
    std::cout << "T = " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "param = " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << std::endl;
}

int main() {
    const int a = 10;
    f(a);
}
