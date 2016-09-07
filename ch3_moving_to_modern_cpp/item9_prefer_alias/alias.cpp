#include <string>

class Widget {
public:
};

template <typename T>
class MyAlloc {
};

template<typename T, typename Alloc>
class List {
};

// 2. C++11 using
template<typename T>
using MyAllocList = List<T, MyAlloc<T>>;

// 2. C++98 typedef
template<typename T>
struct MyAllocList2 {
    typedef List<T, MyAlloc<T>> type;
};

// If using MyAllocList2 in a template class, typename keyword needed
// dependent types must be preceded by typename
template<typename T>
class C {
public:
    typename MyAllocList2<T>::type list;

    MyAllocList<T> list2; // no typename, no ::type
};

// implementatoin of remove_const
template<class T>
struct remove_const {
    typedef T type;
};
template<class T>
struct remove_const<const T> {
    typedef T type;
};

template<class T>
using remove_const_t = typename remove_const<T>::type;

int main() {
    // 1. using alas may be easier
    typedef void (*FP)(int, const std::string&);  // typedef
    using FP2 = void (*)(int, const std::string&); // alias declaration

    // 2. with template
    MyAllocList<Widget> lw;
    MyAllocList2<Widget>::type lw2;

    // 3. type_traits
    std::remove_const<const int>::type a;
    std::remove_const_t<const int> b;  // C++14

    remove_const_t<const int> c;
    c = 4;
}

