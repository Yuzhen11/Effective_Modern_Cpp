# Item 31: Avoid default capture modes

Two default capture modes in C++11: by-reference and by-value.

## By-reference

Problems: The reference to a local variable maybe dangle.

If the closure will be used immediatedly and won't be copied, there's no risk to refer to a local variable. 

Use explicit capture list to remind us to perform lifetime analysis.

Captures apply only to non-satic local variable visible in the scope where the lambda is created.

C++14, generalized lambda capture.

static object can be used inside lambdas but hey can't be captured!!! Looks like passed-by reference


## Things to Remember

* Default by-reference capture can lead to dangling references.

* Default by-value capture is susceptible to dangling pointers (especially this), 
and it misleadingly suggests that lambdas are self-contained.
