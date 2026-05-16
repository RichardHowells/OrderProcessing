### Using the Standard Template Library

#### Upgrade the two pointers in Portfolio to a vector

1. Working in `portfolio.h/.cpp`
1. Replace the two `Product *` pointers with an `std::vector` of `Product` pointers.  The portfolio does not own the `Product` objects, so these are non-owning pointers you should **not** use a smart pointer. You should not add a destructor
1. Fix the issues this causes in the `.cpp` file:
	1. The copy constructor - copy the vector in the initializer list
	1. `operator =` - assign the incoming vector over the member variable.  The vector's `operator =` knows what to do
	1. in `addProduct` - use `push_back` to add the incoming pointer to the vector
	1. in `averageProductValue` - use a for loop to count the number of items and compute the totalValue

	### Bonus ideas

	#### Use iterators to manage the for loop

	**NOTE** The range for loop is best practice here, but you will see the iterators used in older code, so take the chance to practice them

1. Convert the for loop to use iterators  
	 					
	An iterator identifies a location in the vector; so `*it` is required to return an actual item from the vector; that item is a `Product *`, which you then need to follow to the actual object.

	#### Use an algorithm to add up the values.  Technically std::accumulate performs a 'left fold' 

1. Use std::accumulate to perform a left fold over the entire collection

	1. `std::accumulate` can iterate over the vector and add each item in the vector to a running total.  We don't want to add up the pointers.  So...
	1. Use the overload that wants a start value (`0.0`) and a function.  The function is executed for each item in the vector.
	1. The function is passed the current running total (a `double`) and an item from the vector (a `Product *`).  It should return a new value for the running total
	1. Write a lambda expression to add the result of `p->getValue(1)` to the current running total
	1. This `accumulate` call will give you the total to go into the average calculation.  the vector's `size()` function will tell you how many entries there are

