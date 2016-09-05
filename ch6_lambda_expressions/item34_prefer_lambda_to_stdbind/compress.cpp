#include <functional>

class Widget {
public:
};

enum class CompLevel {Low, Normal, High};

Widget compress(const Widget& w, CompLevel lev) {
}

int main() {
    Widget w;

    using namespace std::placeholders;

    // w is passed by value
    auto compressRateB = std::bind(compress, w, _1);

    auto compressRateL = [w](CompLevel lev) {  // w is passed by value
        return compress(w, lev);
    }

    compressRateL(CompLevel::High);  // arg is passed by value

    compressRateB(CompLevel::High);  // how is arg passed?
    // Ans: all arguments passed to bind objects are passed by reference, because the function
    // call operator for such objects uses perfect forwarding.

}
