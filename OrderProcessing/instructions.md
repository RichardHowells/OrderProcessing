## Working with global (stand-alone) functions

1. Write a function (`getStockValue`)
    - accept two double values `price` and `quantity`.
    - return the product as a `double`

1. Test it by calling from `main`
    - use a line like this to display the result on `stdout`
    ```
    std::cout << getStockValue(10, 50) << "\n"; 
    ```

1. Add an overload for `getStockValue`
    - accept just the `price`
    - use the fixed value 100.0 as a multiplier for the quantity

1. Test your overload by calling it from `main`

