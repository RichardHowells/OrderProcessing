## Program Organisation

### Use a function declaration
1. Move the `getStockValue` function below the `main` function
1. Notice that the code will not compile.  C++ requires that the function is at least declared before use
1. Add a function declaration above `main`
1. Discover that auto cannot work in this case.  Change the function return type to `double` (two places)
1. The program should now run as before
### Separately compile the function
1. Move the function declaration into a new header file `stockvalue.h`
1. `#include` that file into `OrderProcessing.cpp`
1. Move the function definition into a new implementation file `stockvalue.cpp`
1. `stockvalue.cpp` should also `#include "stockvalue.h"`
1. The program should work as before
1. Add a for loop to iterate over the integers 0 to 9
1. Inside the loop if i is even display the result of calling `getStockValue` with a price of 10 * i, and a quantity of 50
1. if i is odd display the result of calling `getStockValue` with a price of 20 * i, and a quantity of 50

1. Test it by calling from `main`
    - use a line like this to display the result on `stdout`
    ```
    std::cout << getStockValue(10, 50) << "\n"; 
    ```

1. Add an overload for `getStockValue`
    - accept just the `price`
    - use the fixed value 100.0 as a multiplier for the quantity

1. Test your overload by calling it from `main`

## Bonus ideas

1. Remove (maybe comment out) the single parameter overload.  On the double parameter overload give quantity a default argument of 100. The program should work unchanged

1. Try using the `auto` keyword to infer the type of any local variables in your code. The program should work unchanged

1. Try using `auto` as the return type on your function(s). The program should work unchanged.  We will find out later that there are limited circumstances where `auto` return type is allowed


