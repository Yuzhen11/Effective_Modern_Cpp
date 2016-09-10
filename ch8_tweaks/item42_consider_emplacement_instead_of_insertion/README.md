# Item 42: Consider emplacement instead of insertion

## emplacement

    std::vector<std::string> vs;
    vs.push_back("xyzzy");

    vs.push_back(std::string("xyzzy"));  // the same

Create a temp object, move, and destroy the temp object.

    vs.emplace_back("xyzzy");  // constuct std::string directly inside vs

Insertion functions take objects to be inserted.

Emplacement functions take constructor arguments for objects to be inserted.

    std::string s("abc");
    vs.push_back(s);  // copy construct 
    vs.emplace_back(s);  // the same

## Some situations

1. use push_back for std::vector<std::shared_ptr<Widget>> for exception safety. 
Memory leak when some exception throws in emplace_back.

2. emplace_back enable explicit constructor

    std::vector<std::regex> regexes;

    std::regex r = nullptr;  // error, won't compile
    regexes.push_back(nullptr);  // error, won't compile, copy init

    regexes.emplace_back(nullptr);  // compiles, direct init, use explicit constructor

    std::regex r1 = nullptr;  // copy initialization. explicit constructor not permitted
    std::regex r2(nullptr);  // direct initialization. explicit constructor is permitted

## Things to Remember

* In principle, emplacement functions should sometimes be more efficient than 
their insertion counterparts, and they should never be less efficient.

* In practice, they're most likely to be faster when 1. the value being added is constructed
into the container, not assigned; 2. the argument types passed differ from the type held be the container;
and 3. the container won't reject the value being added due to it being a duplicate.

* Emplacement functions may perform type conversions that would be rejected by insertion functions.
