# Item 27: Famiiarize yourself with alternatives to overloading on universal references.

## Abondaon overloading

## Pass by const T&

## Pass by value

## Use Tag dispatch

Add addition parameter as tag to pass the type info.

    template<typename T>
    void logAndAdd(T&& name) {
        logAndAddImpl(
            std::forward<T>(name), 
            std::is_integral<typename std::remove_reference<T>::type>()
        );
    }

    template<typename T>
    void logAndAddImpl(T&& name, std::false_type) {  // If it's not integral
        names.emplace(std::forward<T>(name));
    }

    std::string nameFromIdx(int);
    void logAndAddImpl(int idx, std::true_type) {  // If it's integral
        logAndAdd(nameFromIdx(idx));  // Invoke logAndAdd again
    }

## Constraining templates that take universal references

What if in constructor?

SIFANE

enable_if

    class Person {
    public:
        template<typename T, 
                 typename = std::enable_if_t<
                    !std::is_base_of<Person, std::decay_t<T>>::value
                    &&
                    !std::is_integral<std::remove_reference_t<T>>::value
                    >
                 >
        explicit Person(T&& n): name(std::forward<T>(n)) {}  // ctor for std::strings and args convertible to std::strings

        explicit Person(int idx) {}  // ctor for integral args
    private:
        std::string name;
    };

## Tradeoffs

The error message of using enable_if may be hard to track.

## Things to Remember

* Alternatives to the combination of universal references and overloading include the use of distinct functions names,
passing parameters by lvalue-reference-to-const, passing parameters by value and using tag dispatch.

* constraining templates via std::enable_if permits the use of unversal referecnes and overloading together, 
but it controls the conditions under which compilers may use the universal reference overloads.

* Universal reference parameters often have efficiency advantages, but they typeically have usability disadvantages.
