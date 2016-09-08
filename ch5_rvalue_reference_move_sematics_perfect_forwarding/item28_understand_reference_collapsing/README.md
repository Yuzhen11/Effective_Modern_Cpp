# Item 28: Understand reference collapsing

Again universal reference

    template<typename T>
    void func(T&& param);

When an lvalue is passed as an argument, T is deduced to be an lvalue reference.
When an rvalue is passed, T is deduced to be a non-reference.

    Widget widgetFactory();

    Widget w;

    func(w);  // T deduced to be Widget&

    func(widgetFactory()); // T deduced to be Widget

When we pass a lvalue, T is deduced to be lvalue reference, then what about T&&?
    
    func(w);

    void func(Widget& &&);

    void func(Widget&);  // reference collapsing!

## Reference Collapsing Rule

If either reference is an lvalue reference, the result is an lvalue reference.
Otherwise, the result is an rvlue reference.

& && -> &

&& & -> &

& & -> &

&& && -> &&

## std::forward

    template<typename T>
    T&& forward(typename remove_reference<T>::type& param) {
        return static_cast<T&&>(param);
    }

    template<T>
    void f(T&& param) {
        someFunc(std::forward<T>(param));
    }

1. The argument passed to f is lvalue of type Widget. T will be deduced to Widget&. 

f will look like:

    f(Widget& param) {
        someFunc(std::forward<Widget&>(param));
    }

std::forward will look like:
    
    Widget& && forward(typename remove_reference<Widget&>::type& param) {
        return static_cast<Widget& &&>(param);
    }
    // remove reference -> 
    Widget& && forward(Widget& param) {
        return static_cast<Widget& &&>(param);
    }
    // reference collapsing->
    Widget& forward(Widget& param) {
        return static_cast<Widget&>(param);
    }

Does nothing!!!

2. The argument passed to f is rvalue of type Widget. T will be deduced to Widget.

f will look like:
    
    f(Widget&& param) {
        someFunc(std::forward<Widget>(param));
    }

std::forward will look like:
    
    Widget&& forward(typename remove_reference<Widget>::type& param) {
        return static_cast<Widget&&>(param);
    }
    // remove reference ->
    Widget&& forward(Widget& param) {
        return static_cast<Widget&&>(param);
    }
    // no reference collapsing

std::forward will trun f's parameter param (an lvalue!!!) into an rvalue.
The end result is that an rvalue argument passed to f will be forwarded to someFunc as an rvalue, 
which is precisely what is supposed to happen.

## auto reference collapsing

Basically the same.

Case 1

    Widget w;
    auto&& w1 = w;
    // auto is deduced to be Widget& (consider template)
    Widget& && w1 = w;
    // reference collapsing
    Widget& w1 = w;

Case 2
    
    auto&& w2 = widgetFactory();
    // auto is deduced to Widget
    Widget&& w2 = widgetFactory();

## Things to Remember

* Reference collapsing occurs in four contexts: template instantiation, auto type generation, creation and use of 
typedef's and alias declaration, and decltype.

* When compilers generate a reference to reference in a reference collapsing context, the result is a single referece. See above....

* Universal reference are rvalue references in contexts where type deduction distinguishes lvalues from rvalues and
where reference collapsing occurs.
