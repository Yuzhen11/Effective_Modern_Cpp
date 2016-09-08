#include <string>

class Widget {
public:
    Widget(Widget&& rhs)
        :name(std::move(rhs.name))
    {}

    template<typename T>
    void setName(T&& newName) {
        name = std::forward<T>(newName);
    }

    template<typename T>
    void setName(T&& newName) {
        name = std::move(newName); // Compiles, but bad, bad, bad!
    }
    // Suppose we just want to setName() with lvalue
    // but setName function make my variable moved...
    //
    // std::string getWidgetName();  // factory function
    //
    // Widget w;
    //
    // auto n = getWidgetName();  // n is a local variable
    //
    // w.setName(n);  // move n into w! n's value now unknown

private:
    std::string name;

};

class Widget2 {
public:
    // set from const lvalue
    void setName(cosnt std::string& newName) {
        name = newName;
    }
    // set from rvalue
    void setName(std::string&& newName) {
        name = std::move(newName);
    }
priate:
    std::string name;
};

int main() {
}
