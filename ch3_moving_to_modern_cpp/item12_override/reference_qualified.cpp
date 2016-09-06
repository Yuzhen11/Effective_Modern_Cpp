#include <iostream>

class Widget {
public:
    void doWork() & {
        std::cout << "lvalue..." << std::endl;
    }
    void doWork() && {
        std::cout << "rvalue..." << std::endl;
    }
};

Widget makeWidget() {
    return Widget();
}
int main() {
    Widget w;
    w.doWork();  // lvalue

    makeWidget().doWork(); // rvalue
    Widget().doWork();  // rvalue

}
