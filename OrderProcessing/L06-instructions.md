## Pointers and references

### Create a class to model a Portfolio

#### Create the class skeleton
1. Add a file `portfolio.h`
1. Add the skeleton of a class `Portfolio`.  `class Portfolio` should be in the namespace `mallon::cpp`
1. Add a standard header guard to the file
1. Add a file `portfolio.cpp`.  For the skeleton class it has only the line `#include 'portfolio.h'` and an empty namespace
	```C++
	namespace mallon::cpp
	{
	}
	```

	#### Make `class Portfolio` hold pointers to two `Stock` objects
1. Add `private` members for two pointers to `Stock` named `stock1` and `stock2` initialized with `nullptr`
1. Add a public `addStock` method taking a `Stock` pointer.
	1. Implement `addStock` to check if `stock1` is empty (ie `== nullptr`)
	1. If `stock1` is empty then store the incoming parameter in `stock1`
	1. If `stock1` has a value then store the incoming parameter in `stock2`
1. Add a public `averageStockPrice()` function to calculate the average price of the stocks in the portfolio.  It should:
	1. return zero if there are no stocks in the portfolio
	1. otherwise add up the total of the prices and divide by the count of prices
1. Back in `OrderProcessing.cpp`
1. Near the bottom of the file (after the loops) create a `Portfolio` object
1. Display its `averageStockPrice`
1. Add the `apple` stock object to it. (The function expects a pointer; pass `&apple`)
1. Discover that this won't work. The `apple` object is declared `const` and its address cannot be passed to a non-const pointer.  Remove the `const` qualifier from `apple` (This makes business sense.  You would not normally expect a stock's price to remain constant)
1. Display the new `averageStockPrice`
1. Add the `microsoft` object to the portfolio
1. Display the new `averageStockPrice`
1. Check that the averages are correctly calculated

	### Use pass by reference
1. Add a namespace level function `comparePortfolios` above the `main` function. Implement it to... 
	1. expect two `Portfolio` references `p1` and `p2`
	1. print a message if `p1` has the highest `averageStockPrice`
	1. print a message if `p2` has the highest `averageStockPrice`
	1. print a message if the two portfolios have equal `averageStockPrice`
1. Back in `OrderProcessing.cpp` create a few more `Portfolio` objects to test all three branches of this function
	## Bonus ideas
1. The `comparePortfolios` function has no business modifying the passed in portfolio objects.  Declare the parameters as `const` references. **NOTE** this may refuse to compile if the `averageStockPrice` function is non-const.  Go back and declare `averageStockPrice` as `const`. This is a good example of how adding `const` later can begin to ripple through a code base

1. Create an overload of the `comparePortfolios` function, to take in two `Stock` pointers.  This also has no business modifying the passed in portfolio objects.  Declare the parameters as `const` pointers. **NOTE** the `averageStockPrice` function should be `const` by now so this should compile. This is a good example of how adding `const` later can begin to ripple through a code base
1. Call this overload by passing the addresses of `Portfolio` objects

