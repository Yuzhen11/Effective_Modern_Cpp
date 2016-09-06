#include <vector>
#include <algorithm>
#include <iterator>

void test98() {
    typedef std::vector<int>::iterator IterT;
    typedef std::vector<int>::const_iterator ConstIterT;
    std::vector<int> values;

    ConstIterT ci = std::find(static_cast<ConstIterT>(values.begin()), 
                              static_cast<ConstIterT>(values.end()),
                              1983);
    // values.insert(static_cast<IterT>(ci), 1998);  // Error
}

void test11() {
    std::vector<int> values;
    auto it = std::find(values.cbegin(), values.cend(), 1983);  // cbegin and cend
    values.insert(it, 1998);
}

template<typename C, typename V>
void findAndInsert(C& container, const V& targetVal, const V& insertVal) {
    using std::cbegin;
    using std::cend;

    auto it = std::find(cbegin(container), cend(container), targetVal);  // More general: non-member cbegin, cend
    // container.insert(it, insertVal);
}

template<class C>
auto cbegin(const C& container) -> decltype(std::begin(container)) {
    return std::begin(container);  // since container is const, std::begin() yields a const_iterator
}

void test() {
    int a[] = {1,2,3,4};
    findAndInsert(a, 3, 5);

    std::vector<int> b{};
    findAndInsert(b, 2, 3);
}

int main() {
    test11();
    test();
}
