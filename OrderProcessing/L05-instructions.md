## Classes

### Create a class to model an individual Stock

1. Working in `stockvalue.h` declare a `class Stock`
1. It should have a `ticker` (`std::string`) and a `price` (`double`) as member variables
1. Each member should have the pair of `getXX` and `setXX` functions
1. Move the `getStockValue` function into the class.  It should now only take the `quantity` parameter, and use the `price` value from the class' member variable
1. In `OrderProcessing.cpp` find the area of the code that works with `getStockValue`.
1. Before that code create a `Stock` object.  Use the `setXX` functions to set the ticker to 'AAPL' and the price to 50.
1. Display the result of calling the member function getStockValue for Apple ('AAPL')
1. Create a second `Stock` object and initialize it with the values 'MSFT'/75
1. Display the result of calling the member function getStockValue for Microsoft ('MSFT')
1. Adjust the code in the loops to use the Apple and Microsoft objects

	### Bonus ideas
	#### Small or trivial functions are often implemented `inline`.  
1. Implement the `getPrice` function directly in the class declaration.  Doing this is implicitly a request to inline the function.  Delete it from the `.cpp` file
1. Implement the `getTicker` function directly **after** the class declaration (but still in the `.h` file).  This will require the `inline` keyword. Delete it from the `.cpp` file
1. Your code should still run exactly as before
	#### Most classes should have a constructor function to perform initialization duties
1. Add a constructor to `class Stock`.  You **should** use the constructor initialisation list because it is the best practice.  Your constructor should accept both ticker and price as parameters
1. You will discover that your `OrderProcessing.cpp` file will not compile.  
1. Add constructor parameters to the definitions for the two `Stock` objects.  Remove the `setXX` calls, they are no longer needed
1. Your code should still run exactly as it did before
	#### Accessor functions (ie non-mutating functions) should be declared const
1. In `OrderProcessing.cpp` declare the Apple `Stock` object as `const`
1. Try to compile and see the compiler complain about calling non-const functions.  (Note - the compiler diagnostic message is unlikely to be straightforward)
1. Declare the getter functions `getPrice` `getTicker` `getStockValue` as `const`.  If the function is implemented outside the class `const` must appear in the implementation **as well as** the declaration
1. Your code should run exactly as it did before.