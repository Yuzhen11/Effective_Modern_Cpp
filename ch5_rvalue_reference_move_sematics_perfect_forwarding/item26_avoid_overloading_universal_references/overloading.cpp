#include <set>
#include <string>

std::multiset<std::string> names;

template<typename T>
void logAndAdd(T&& name) {
    // ...
    names.emplace(std::forward<T>(name));
}

// overloading for int
void logAndAdd(int idx) {
}

class Person {
public:
    template<typename T>
    explicit Person(T&& n):name(std::forward<T>(n)) {}  // perfect forwarding ctor

    explicit Person(int idx) {}  // int ctor

    Person(const Person& rhs) {  // copy-ctor (compiler-generated)
    }
    Person(Person&& rhs) {  // move-ctor (compiler-generated)
    }
private:
    std::string name;
};


int main() {
    {
        std::string petName("Dala");
        logAndAdd(petName);  // lvalue
        logAndAdd(std::string("Perrrll")); // rvalue
        logAndAdd("Dog");  // string literal
    }
    {
        logAndAdd(22);  // call int overload
        short nameIdx;

        // logAndAdd(nameIdx);  // error! 
        // universal reference overload was a better match
    }
    {
        Person p("Nancy");
        // auto cloneOfp(p);   // won't compile
        // try to match universal reference
    }
}
