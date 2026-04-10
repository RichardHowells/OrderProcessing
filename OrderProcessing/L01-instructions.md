## Program Organisation

### Use a function declaration
1. Move the `getStockValue` function definition below the `main` function
1. Notice that the code will not compile.  C++ requires that the function is at least declared before use
1. Add a function declaration for `getStockValue` above `main`
1. Discover that auto cannot work in this case.  Change the function return type to `double` (two places)
1. The program should now run as before
### Separately compile the function
1. Move the function declaration into a new header file `stockvalue.h`
1. `#include` that file into `OrderProcessing.cpp`
1. Move the function definition into a new implementation file `stockvalue.cpp`
1. `stockvalue.cpp` should also `#include "stockvalue.h"`
1. The program should work as before
### Use the `for` loop and the `if`
1. Add a `for` loop to iterate over the integers 0 to 9
1. Inside the loop if `i` is even display the result of calling `getStockValue` with a price of `10 * i`, and a quantity of 50
1. if `i` is odd display the result of calling `getStockValue` with a price of `20 * i`, and a quantity of 50

### Bonus ideas
1. Rewrite the loop to use a `while` so that it produces the exact same output as the for loop
1. Rewrite the `if` inside the loop to use a `switch` (if you used `switch` first time around then rewrite to use `if`) 
