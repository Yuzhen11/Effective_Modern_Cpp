template<typename T>
class TD;

// This cpp file cannot compile! Just used for seeing the type deduced
int main() {
    const int theAns = 42;
    auto x = theAns;
    auto y = &theAns;
    TD<decltype(x)>();
    TD<decltype(y)>();
}
