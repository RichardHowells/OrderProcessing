## Program Organisation and Overloading

### Use a function declaration
1. Move the `getStockValue` function below the `main` function
1. Notice that the code will not compile.  C++ requires that the function is at least declared before use
1. Add a function declaration for `getStockValue` above `main`
1. Discover that in this case `auto` cannot deduce the function return type.  Change the function return type to `double` (two places)
1. The program should now run as before

    ### Separately compile the function
1. Move the function declaration into a new header file `stockvalue.h`
1. `#include` that file into `OrderProcessing.cpp`
1. Move the function definition into a new implementation file `stockvalue.cpp`
1. `stockvalue.cpp` should also `#include "stockvalue.h"`
1. The program should work as before

1. Test it by calling from `main`. Use a line like this to display the result on `std::cout`
    ```
    std::cout << getStockValue(10, 50) << "\n"; 
    ```
    ### Namespaces
1. Working in the `stockvalue.h/.cpp` files; package the function in a nested namespace `mallon::cpp`. 
1. Adjust the code in `main` to call the namespace's function.  Try
	1. a fully qualified name
	1. a `using namespace ...` declaration at the top of the file

1. Add an overload for `getStockValue`
    - accept just the `price` as a parameter
    - use the fixed value `100.0` as a multiplier for the quantity

1. Test your overload by calling it from `main`

    ### Use a for loop and an if
1. Add a `for` loop to iterate `i` over the integers 0 to 9
1. Inside the loop if `i` is even display the result of calling `getStockValue` with a price of `10 * i`, and a quantity of `50`
1. if `i` is odd display the result of calling `getStockValue` with a price of `20 * i`, and a quantity of `50`


    ## Bonus ideas

1. Remove (maybe comment out) the single parameter overload.  On the double parameter overload give `quantity` a default argument of `100`. The program should work unchanged. 

    **NOTE** Default arguments can remove the need for extra overloads

1. Try using the `auto` keyword to infer the type of any local variables in your code. The program should work unchanged

    ### Use a while loop and a switch
1. Rewrite the loop to use a `while` so that it produces the exact same output as the `for` loop
1. Rewrite the `if` inside the loop to use a `switch` (if you used `switch` first time around then rewrite to use `if`) 

