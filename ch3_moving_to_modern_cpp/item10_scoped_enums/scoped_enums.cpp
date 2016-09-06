#include <cstdint>
#include <tuple>

template<typename E>
constexpr typename std::underlying_type<E>::type
toUType(E enumerator) noexcept {
    return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

// C++14
template<typename E>
constexpr typename std::underlying_type_t<E>
toUType2(E enumerator) noexcept {
    return static_cast<typename std::underlying_type_t<E>>(enumerator);
}

// C++14
template<typename E>
constexpr auto 
toUType3(E enumerator) noexcept {
    return static_cast<typename std::underlying_type_t<E>>(enumerator);
}

int main() {

    // 1.
    // enum Color {black, white, red};  // black, white, red are in same scope as Color
    // auto white = false;  // error! white already declared in this scope

    enum class Color {black, white, red}; // scoped to Color
    auto white = false;  // fine, no other

    // Color c = white; // error
    Color c1 = Color::white;  // ok
    auto c2 = Color::white;  // ok


    // 2.
    enum C {a,b,c};
    C t = a;
    int num = t;

    enum class C2 {a, b, c};
    C2 t2 = C2::a;
    // int num2 = t2;  // error, cannot convert implicitly
    int num3 = static_cast<int>(t2);

    // 3.
    enum class Status: std::uint32_t;  // declartion
    enum class Status: std::uint32_t { // definition
        good = 0,
        failed = 1,
        indeterminate = 0xFFFFFFFF
    };

    // 4.
    using UserInfo = 
        std::tuple<std::string, std::string, std::size_t>;

    UserInfo uInfo;
    auto val = std::get<1>(uInfo);

    // unscoped enum
    enum UserInfoFields{uiName, uiEmail, uiReputation};
    auto val1 = std::get<uiEmail>(uInfo);  // get

    // scoped enum, too long...
    enum class UserInfoFields2{uiName, uiEmail, uiReputation};
    auto val2 = std::get<static_cast<std::size_t>(UserInfoFields2::uiEmail)>(uInfo);

    // Need to be known at compile time
    auto val3 = std::get<toUType(UserInfoFields2::uiEmail)>(uInfo);
    auto val4 = std::get<toUType2(UserInfoFields2::uiEmail)>(uInfo);
    auto val5 = std::get<toUType3(UserInfoFields2::uiEmail)>(uInfo);

}
