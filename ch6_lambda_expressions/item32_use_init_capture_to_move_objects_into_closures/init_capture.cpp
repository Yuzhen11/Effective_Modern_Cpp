#include <memory>
#include <iostream>

class Widget {
public:
private:
};

int main() {
    auto pw = std::make_unique<Widget>();
    auto func = [pw = std::move(pw)] {};
}
