# Item 6: Use the explicitly typed initializer idiom when auto deduces undesired types

Sometimes, the auto may offer undesired type.

    std::vector<bool> features(const Widget& w);

    Widget w;
    bool highPriority = features(w)[5];
    processWidget(w, highPriority);

    // Use auto ?
    auto highPriority = features(w)[5];
    processWidget(w, highPriority);  // Undefined behavior!

`std::vector<bool>::operator[]` return an object of type `std::vector<bool>::reference`.

`std::vector<bool>` represent its bools in packed form, one bit per bool. Cannot return reference

One implemenation of `std::vector<bool>::reference` contains a pointer to the machine word holding the referenced bit, plus the offset.

Using auto, the auto will be type `std::vector<bool>::reference`, with a pointer to a word in *temp*, so making the processWidget undefined behavior.

`std::vector<bool>::reference` is called proxy classes.

Proxy class include shared_ptr, uniq_ptr and so on.

    Matrx sum = m1 + m2 + m3 + m4;

operator + for two Matrix objects would return an object of a proxy class such as `Sum<Matrix, Matrix>`. May be more efficient.

As a generaly rule, "invisible" proxy classes don't play well with auto. Objects of such classes are often not designed to live longer than a single statement.

Solution: the explicitly typed initializer idiom

    auto highPriority = static_cast<bool>(features(w)[5]);

deliberately cast ...
    
    double calcEpsilon();
    float ep = calcEpsilon();
    auto ep = static_cast<float>(calcEpsilon());

## Things to remember

* "Invisible" proxy types can casue auto to deduce the "wrong" type for an initializing expression.

* The explicitly typed initializer idiom forces auto to deduce the type you want it to have.
