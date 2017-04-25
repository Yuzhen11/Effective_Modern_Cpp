# Use std::move on rvalue references, std::forward on universal references

## Standard usages of std::move and std::forward

rvalue references bind only to objects that are candidates for moving.

The way to do that is to cast parameters bound to such objects to rvalues.

Universal reference should be cast to rvalues only if they are initialized with rvalues.

    class Widget {
    public:
        Widget(Widget&& rhs)  // rhs definitely refer to an object eligible for moving
            :name(std::move(rhs.name))
        {}

        // newName is universal reference
        template<typename T>
        void setName(T&& newName) {
            name = std::forward<T>(newName);
        }

    private:
        std::string name;

    };

## Don't use them interchangably

* Should not use std::forward on rvalue references (replacing std::move), see Item 23.

* Shoule not use std::move with universal references, because that can have the effect of unexpectedly
modifying lvalues. See cpp.
```c++
    template<typename T>
    void setName(T&& newName) {
        name = std::move(newName); // Compiles, but bad, bad, bad!
    }
    // Suppose we just want to setName() with lvalue
    // but setName function make my variable moved...
    
    std::string getWidgetName();  // factory function
    
    Widget w;
    
    auto n = getWidgetName();  // n is a local variable
    
    w.setName(n);  // move n into w! n's value now unknown
```

##  What about replace universal reference with two functions?

    class Widget2 {
    public:
        // set from const lvalue
        void setName(cosnt std::string& newName) {
            name = newName;
        }
        // set from rvalue
        void setName(std::string&& newName) {
            name = std::move(newName);
        }
    priate:
        std::string name;
    };

Can work, but drawbacks:

1. More source code to write and maintain.

2. Less efficient. (w.setName("Adela Novak"));

The most serious problem: The scalability of the design.

n parameters necessitates 2^n overloads. What about unlimited number of parameters.

    tamplate<class T, class... Args>
    shared_ptr<T> make_shared(Args&&... args);

For these functions, universal references are the only way to go.

## Use the object bound to an rvalue reference or a universal reference more than once

    template<typename T>
    void setSignText(T&& text) {
        sign.setText(text);  // use text, but don't modify it.
        // ?? setText can modify the text ??

        signHistory.add(std::forward<T>(text));  // conditionally cast text to rvalue
    }

## Apply std::move and std::forward to return value

    Matrix operator+(Matrix& lhs, const Matrix& rhs) {
        lhs += rhs;
        return std::move(lhs);
        // return lhs;  // copy lhs into return value
    }

    template<typename T>
    Fraction reduceAndCopy(T&& frac) {
        frac.reduce();
        return std::forward<T>(frac);  // move rvalue into return value, copy lvalue
    }

If std::forward were omitted, frac would be unconditionally copied into
reduceAndCopy's return value! (The difference with the next part is frac is T&& I think)

## Don't apply in returning local variable (RVO)

    Widget makeWidget() {
        Widget w;
        ...
        return w;
        // return std::move(w);  // no, compiler will help
    }

Return value optimization

1. They type of the local object is the same as that returned by the function.

2. The local object is what's being returned.

    Widget makeWidget(Widget w) {
        return w;
    }

In this case, compiler will use move...

Compiler will help to try to use RVO, if not, move~

## Things to Remember

* Apply std::move to rvalue references and std::forward to 
universal references the last time each is used.

* Do the same thing for rvalue references and universal references
being returned from functions that return by value.

* Never apply std::move or std::forward to local object
if they would otherwise be eligible for the return value optimization.


