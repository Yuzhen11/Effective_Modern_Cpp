#include <string>
#include <type_traits>

// C++11
template<typename T>
typename std::remove_reference<T>::type&&
move(T&& param) {
    using ReturnType = 
        typename std::remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}

// C++14
namespace cpp14 {
template<typename T>
decltype(auto) move(T&& param) {
    using ReturnType = 
        typename std::remove_reference_t<T>&&;
    return static_cast<ReturnType>(param);
}
}

class Annotation {
public:
    explicit Annotation(const std::string text)
        :value(std::move(text)) {}
    // "move" text into value; this code doesn't do what it seems to!
    // Due to const!!!
private:
    std::string value;
};

int main() {
    int a = 10;
    int b = move(a);
    int c = cpp14::move(a);
}
