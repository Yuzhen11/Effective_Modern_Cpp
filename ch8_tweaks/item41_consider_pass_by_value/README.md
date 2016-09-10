# Item 41: Consider pass by value for copyable parameters that are cheap to move and always copy

Approach 1:

    class Widget {
    public:
        void addName(const std::string& newName) {   // take lvalue
            names.push_back(newNamer);
        }
        void addName(std::string&& newName) {  // take rvalue
            names.push_back(std::move(newNamer));
        }
    private:
        std::vector<std::string> names;
    }

Drawbacks:

Two functions to declare, to implement, to document, to maintain...

Cost summary:

one copy for lvalue, one move for rvalue.
    
Approach 2:

    class Widget {
    public:
        template<typename T>
        void addName(T&& newName) {   // take lvalue and ravlue
            names.push_back(std::forward<T>(newNamer));
        }
    private:
        std::vector<std::string> names;
    }

Drawbacks:

Bloated header files, odd failure cases, and confounding error messages.

Cost summary:

one copy for lvalue, one move for rvalue.
More efficient for other types (literal) item 25.

Approach 3:

    class Widget {
    public:
        void addName(std::string newName) {   // take lvalue and ravlue
            names.push_back(std::move(newNamer));
        }
    private:
        std::vector<std::string> names;
    }

Cost summary:

one copy plus one move for lvalue, two moves for rvalue.

## Why we consider pass-by-value

1. You should only consider using pass by value...(what's this...). one function only

2. Consider pass by value only for copyable parameters. If the parameter is move-only, only the one
function for rvalue is enough. Also avoid the two moves cost.

3. Pass by value is worth considering only for parameter that are cheap to move. Think about additional 
move cost for both lvalue and rvalue.

4. You should consider pass by value only for parameters that are always coped. Sometimes, there are some
additional check, and may not copy at all. Then in this case, pass-by-value waste the copy...

## Copy using assignment

    class Password {
    public:
        explicit Pasword(std::string pwd)  // pass by value construct text
        : text(std::move(pwd)) {}

        void changeTo(std::string newPwd) {  // pass by value assign text
            text = std::move(newPwd);
        }
    };

Using this method may have additional memory allocation and deallocation.

Free old memory and construct new memory.

If the newPwd is shorter, the following is more efficient:

    void changeTo(const std::string& newPwd) {
        text = newPwd;  // can resue memory if text.capacity() >= newPwd.size()
    }

## Slicing problem

## Things to Remember

* For copyable, cheap-to-move parameters that are always copied, pass by value may be nearly 
as efficient as pass by reference, it's easier to implement, and it can generate less object code.

* For lvalue arguments, pass by value (i.e. copy construction) followed by move assignment may be 
more expensive than pass by reference followed by copy assignment.

* Pass by value is subject to slicing problem, so it's typically inappropriate for base class parameter types.
