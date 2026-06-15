## Working with global (stand-alone) functions

1. Write a function (`getValue`)
    - accept two double values `price` and `quantity`.
    - return the product as a `double`
1. Place it above `main` in the file. (A function has to be declared before it is used. Here you are defining the function; a definition is always a declaration.)

1. Test it by calling from `main`
    - use a line like this to display the result on `stdout`
    ```
    std::cout << getValue(10, 50) << "\n"; 
    ```

1. Add an overload for `getValue`
    - accept just the `price`
    - use the fixed value 100.0 as a multiplier for the quantity

1. Test your overload by calling it from `main`

## Bonus ideas

1. Remove (maybe comment out) the single parameter overload.  On the two parameter overload give quantity a default argument of 100. The program should work unchanged

1. Try using the `auto` keyword to infer the type of any non-parameter local variables in your code. The program should work unchanged

1. Try using `auto` as the return type on your function(s). The program should work unchanged.  We will find out later that there are limited circumstances where `auto` return type is allowed


