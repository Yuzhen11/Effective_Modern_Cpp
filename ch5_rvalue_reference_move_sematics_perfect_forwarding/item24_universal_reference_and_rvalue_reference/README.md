# Item 24: Distinguish universal references from rvalue references

## rvalue reference and universal reference

    void f(Widget&& param);  // rvalue reference
    Widget&& var1 = Widget(); // rvalue reference
    auto&& var2 = var1;  // universal reference

    template<typename T>
    void f(std::vector<T>&& param)  // rvalue reference

    template<typename T>
    void f(T&& param)  // universal reference

    
T&& has two different meanings. 

One is rvalue reference:
They bind only to rvalues.

The other meaning is universal reference:
Either rvalue reference or lvalue reference.

Universal reference:

If the initializer is an rvalue, the universal reference
corresponds to an rvalue reference.

If the initializer is an lvalue, the universal reference
corresponds to an lvalue reference.

Even the simple presence of a const qualifier is enough to
disqualify a reference from being universal.

    template<typename T>
    void f(const T&& param);  // param is an rvalue reference

## Examples

In std::vector
    
    template<class T, class Allocator = allocator<T>>
    class vector {
        // When you define a vector, T is already determined
        void push_back(T&& x);  // rvalue reference

        template<class... Args>
        void emplace_back(Args&&... args);  // universal reference
    };

auto&& are universal references. 

Timer:

    auto timeFuncInvocation = 
      [] (auto&& func, auto&&... params) {
          using namespace std::chrono;
          auto start = steady_clock::now();
          // See Item 33
          std::forward<decltype(func)>(func)(
            std::forward<decltype(params)>(params)...
          );
          auto end = steady_clock::now();
          std::cout << duration_cast<duration<double>>(end-start).count() << " seconds" << std::endl;
      };

## Things to Remember

* If a function template parameter type T&& for a deduced type T, 
or if an object is declared using auto&&, the parameter or object is a universal reference.

* If the form of the type declaration isn't precisely type&&, or if type deduction
does not occur, type&& denotes an rvalue referecen.

* Universal reference correspond to rvalue reference if they're initialized with rvalues.
They correspond to lvalue reference if they're initialized with lvalues.
