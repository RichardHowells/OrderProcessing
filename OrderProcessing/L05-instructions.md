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
1. Adjust the loops to use the Apple and Microsoft objects

	### Bonus idea
