#include <functional>

class PolyWidget {
public:
    template<typename T>
    void operator()(const T& param) const {
    }
};

int main() {
    using namespace std::placeholders;

    PolyWidget pw;
    auto boundPW = std::bind(pw, _1);
    boundPW(1930);  // int
    boundPW(nullptr);  // nulltpr
    boundPW("hello");  // string literal
    pw(321);

    auto boundPW2 = [pw](const auto& param) { pw(param); }; // C++14
}
