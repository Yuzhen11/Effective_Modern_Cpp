# Item 17: Understand special member function generation

## C++98

Special member functions: default constructor, destructor, copy constructor, and copy assignment operator

A default constructor is generated only if the class declares no constructors at all (This prevents compilers from creating
a default constructor for a class where you've specified that constructor arguments are required).

Generated special member functions are implicitly public and *inline*.

*Non-virtual* unless the funciton is a destructor in a derived class inheriting from a base class with a virtual destructor.


## C++11

Two more: move constructor and the move assignment operator

The move operations are generated only if they're needed, and if they are generated, they perform "memberwise moves" on non-staic data members of the class.

No guarantee that a move will actually take place.

Like *Move Request*.

Types aren't move-enabled will be "moved" via their copy operation.

**Rule1**

The two copy operations are independent, declaring one doesn't prevent compilers from generating the other.

The two move operations are not independent. If you declare either, that prevents compilers from generating the other.

Rationale: If you declare a move constructor, you are indicating that there's something about how move construction should be implemented.

**Rule2**

Move operations won't be generated for any class that explicitly declares a copy operation.

Rationale: If memberwise copy isn't appropriate for the copy operations, memberwise move probably isn't appropriate for the move operations.

**Rule3**

Declare a move operation causes compilers to disable the copy operations.

Rationale: If memberwise move isn't the proper way to move an object, there's no reason to expect that memberwise copy is the proper way to copy it.

**Rule of Three**

If you declare any of a copy constructor, copy assignment operator, or destructor, you should declare all three.

The existence of user-defined destructor has no impact on compilers's willingness to generate copy operations (Not good, user-defined destructor indicate user-defined copy operations are needed).

So, in C++11, compiler does not generate move operations for a class with a user-declared destructor.

**Move operation are generated only if there three things are true**

1. No copy operations are declared in the class.

2. No move operations.

3. No destructor.

C++11 deprecates the automatic generation of copy operations for classes declaring copy operations or a destructor.

## = defualt

This approach is often useful in polymorphic base classes, i.e., classes defining interface.

Polymorphic base classes normally have virtual destructors. Use the `= default`.

However, a user-declared destructor suppresses generation of the move operations, so if movability is to be supported, `= defualt` often finds a second application.

    class Base {
    public:
        virtual ~Base() = default;

        Base(Base&&) = default;
        Base& operator=(Base&&) = default;

        Base(const Base&) = default;
        Base& operator=(const Base&) = default;
    };

## Another Case

Suppose we have a simple class declares no copy operations, no move operations and no destructor. Compilers will automatically generate these functions.
But sometimes later, add a destructor...

The destructor will suppress move operation!!! And move operation... fall back to copy operations... The code can be compile and run correctly.

So, Put `= default` in copy and move operations.

## Things to remember

* The special member functions are those compilers may generate on their own: default constructor, destructor, copy operations, and move operations.

* Default constructor is generated only if the class contains no user-declared constructors.

* Move operation are generated only for classes lacking explicitly declared move operation, copy operations or a destructor.

* The copy constructor is generated fro classes lacking an explicitly declared copy constructor, and 
it's deleted if move operations is declared. Copy assignment is the same.

* Generation of the copy operations with an explicitly declared destructor is deprecated.

* Member function templates never suppress generation of special member functions.

## Thoughs

In Husky, BaseChannel, BaseObjList has virtual destructor, so move operations and copy operations shoule be `= default`.

ObjT only have user-declared constructor.
