#include <iostream>
#include <vector>

class Widget {
public:
    using DataType = std::vector<double>;
    DataType& data() & {  // for lvalue Widget, return lvalue
        std::cout << "lvalue..." << std::endl;
        return values;
    }
    DataType&& data() && {  // for rvalue Widget, return rvalue
        std::cout << "rvalue..." << std::endl;
        return std::move(values);
    }
private:
    DataType values;
};

Widget makeWidget() {
    return Widget();
}
int main() {
    Widget w;
    auto vals1 = w.data();  // call lvalue overload, copy constructs

    auto val2 = makeWidget().data();  // call rvalue overload, move constructs
}
