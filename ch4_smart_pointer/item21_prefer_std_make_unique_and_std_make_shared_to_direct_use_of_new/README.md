# Item 21: Prefer std::make_unique and std::make_shared to direct use of new

## Why make function

Shorter

    auto spw1(std::make_shared<Widget>());  // with make func
    std::shared_ptr<Widget> spw2(new Widget);  // without make func

Exception safety

    void processWidget(std::shared_ptr<Widget> spw, int priority);

    int computePriority();

    processWidget(std::shared_ptr<Widget>(new Widget), computePriority());  // potential resource leak
    processWidget(std::make_shared<Widget>(), computePriority());  // no potential resource leak
    
Improve efficiency

Using make function, a single chunk of memory to hold both the Widget object and the control block!

Without make function, two allocation. 1. Widget; 2, control block

## Why not make function

Cannot customize deleter

Braced initializers.

Consider creating a very large object, when ref count becomes zero, the memory formally occupied by large object remains
allocated due to weak_ptr.

## Things to Remember

* Compared to direct use of new, make functions eliminate source code duplication, improve exception safety, and 
for std::make_shared and std::allocate_shared, generate code that's smaller and faster.

* Situations where use of make functions is inappropriate include the need to specify custom deleters and a desire
to pass braced initializers.

* For std::shared_ptrs, additional situation where make functions may be ill-advised include 1. classes with custom
memory management and 2. systems with memory concerns, very large objects, and std::weak_ptrs that outlive the 
corresponding std::shared_ptrs.
