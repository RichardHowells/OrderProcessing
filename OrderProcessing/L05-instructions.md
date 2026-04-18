## Classes

### Create a class to model an individual Stock

1. Working in `stockvalue.h` declare a `class Stock`
1. It should have a `ticker` (`std::string`) and a `price` (`double`) as member variables
1. Each member should have the pair of `getXX` and `setXX` functions
1. Move the `getValue` function into the class.  It should now only take the `quantity` parameter, and use the `price` value from the class' member variable
1. In `OrderProcessing.cpp` find the area of the code that works with `getValue`.
1. Before that code create a `Stock` object.  Use the `setXX` functions to set the ticker to 'AAPL' and the price to 50.
1. Display the result of calling the member function `getValue` for Apple ('AAPL') - check that it gives the correct result
1. Create a second `Stock` object and initialize it with the values 'MSFT'/75
1. Display the result of calling the member function `getValue` for Microsoft ('MSFT')
1. Adjust the code in the loops to use the Apple and Microsoft objects

	### Bonus ideas

	#### Header files **should** have include guards to make them safe for multiple inclusion
1. In `OrderProcessing.cpp` include the `stockvalue.h` header twice.  Try to compile.  See that you get error messages
1. Add a header guard to `stockvalue.h`
1. Test that your code runs as it did before
	#### Small or trivial functions are often implemented `inline`.  
1. Implement the `getPrice` function directly in the class declaration.  Doing this is implicitly a request to inline the function.  Delete it from the `.cpp` file
1. Implement the `getTicker` function directly **after** the class declaration (but still in the `.h` file).  This will require the `inline` keyword **AND** will require scoping to the class. Delete it from the `.cpp` file
1. Your code should still run exactly as before
	#### Most classes should have a constructor function to perform initialization duties
1. Add a constructor to `class Stock`.  You **should** use the constructor initialisation list because it is the best practice.  Your constructor should accept both ticker and price as parameters
1. You will discover that your `OrderProcessing.cpp` file will not compile.  
1. Add constructor arguments to the definitions of the two `Stock` objects.  Remove the `setXX` calls, they are no longer needed
1. Your code should still run exactly as it did before
	#### Accessor functions (ie non-mutating functions) should be declared const
1. In `OrderProcessing.cpp` declare the Apple `Stock` object as `const`
1. Try to compile and see the compiler complain about calling non-const functions.  (Note - the compiler diagnostic message is unlikely to be straightforward)
1. Declare the accessor functions `getPrice` `getTicker` `getValue` as `const`.  If the function is implemented outside the class `const` must appear in the implementation **in addition to** appearing on the declaration
1. Your code should run exactly as it did before.

	#### The ticker attribute should be immutable.

	During the lifetime of a `Stock` object, it makes sense that it can change `price`, it makes less sense to allow the `ticker` to change.

1. Make the `ticker` attribute `const`.  This will force removal of the `setTicker` function.  The rest of the code should run as before

