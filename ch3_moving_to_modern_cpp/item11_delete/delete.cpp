class A {
public:
    A() = default;
    A(const A&) = delete;
    A& operator=(const A&) = delete;
};

bool isLucky(int number) {
}

bool isLucky(char) = delete;
bool isLucky(bool) = delete;
bool isLucky(double) = delete;

template<typename T>
void processPointer(T* ptr) {
}

template<>
void processPointer<void>(void* ptr) = delete;

class Widget {
public:
    template<typename T>
    void processPointer(T* ptr) {
    }
};

// public, but deleted
template<>
void Widget::processPointer<void>(void* ptr) = delete;  // declare at namespace

int main() {
    // 1. delete special member functions
    A a;
    // A b(a);  // error

    // 2. delete any function
    isLucky(10);
    // isLucky(true);   // error
    // isLucky(3.5f);   // error
    // isLucky("fdsa"); // error
    
    // 3. delete template instantiations
    void* p;
    // processPointer(p);  // error

    Widget w;
    // w.processPointer(p);  // error
}
