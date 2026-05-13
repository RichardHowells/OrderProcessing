### Inheritance and polymorphism

#### Add a base Product class

1. Working in `stockvalue.h/.cpp`
1. Add a new class `Product` (in this file)
1. Have class `Stock` inherit publically from `Product`
1. Push the two data members `ticker` and `price` up into the `Product` base class
1. Similarly bring the setter and getter functions for `ticker` and `price` up into the base class.  This will require changes in BOTH the `.h` and the `.cpp` files.
1. `Product` will need a parameter constructor to initialize the two fields, and `Stock` will need an adjustment to the constructor initializer list to pass the parameters up to the base class constructor
1. At this point your code should run as before


	#### Add another class, Future

1. Add a class `Future` also publically inheriting from `Product`
1. It will be similar to `Stock`
1. Add a field `double depreciation;` to the Future class.  It will need `ticker` and `price` parameter to pass up to `Product`. Add a constructor parameter to initialize the `depreciation` field

1. Again your code should run as before

	#### Introduce a polymorphic function

1. Add a pure virtual (PV) function declaration to Product

	```C++
	virtual double getValue(double quantity) const = 0;
	```

1. Add `override` declarations in both `Future` and `Stock`
1. Implement `Stock::getValue` to return `quantity * price`
1. Implement `Future::getValue` to return `quantity * price * (1 - depreciation / 100)`

 
	#### Test the getValue function

1. In `OrderProcessing.cpp` change all the calls to `getStockValue` to instead call `getValue` these should run as before

1. Add a definition for a `Future`

	```C++
	Future google { "GOOG", 100 };
	```

	#### Call getValue polymorphically via a base class pointer

1. Define a pointer to `Product`
1. Set it to point to the `apple` `Stock` object
1. Use the pointer to call `getValue` and display the result
1. Repeat making the pointer point to the `google` `Future` object
1. Check that the results are giving the correct calculations

	#### Call getValue polymorphically via a base class reference

1. Repeat using a base class (`Product`) reference.  This is a little tricker because the base class reference variable has to be initialized in its definition and cannot be rebound.  You will need to use a separate reference variable each for `apple` and `google`.  This is not a great use case for references.  References really shine as parameter variables


	### Bonus ideas

	#### See override failures
1. Make a tiny change to the signature of `Stock::getValue` - just removing the `const` would be enough
1. See that the compiler complains

	#### Have Portfolio use the base class Product 

1. In `Portfolio.h/.cpp` change uses of class `Stock` to `Product`
1. At this stage the code should run as before

	#### Refactor Portfolio for clarity
1. Rename `Portfolio::addStock` to `Portfolio::addProduct` this will require changes at the call sites too
1. Rename the two `Stock *` fields.  Eg `stock1` to `product1`.  Change the types from `Stock *` to `Product *`
	
1. Make similar changes to parameter names to remove misleading identifier names

	#### Change name and implementation of Portfolio::averageStockPrice
1. Rename to `averageProductValue`
1. Change the implementation to call the polymorphic `Product::getValue` passing the quantity as `1`
1. In `OrderProcessing.cpp` create a new `Portfolio` object 
	1. Test that you can add both `Stock`s and `Future`s
	1. Check that `averageProductValue` returns the correct result

	#### Separate the three classes `Product`, `Stock`, `Future` into their own `.h/.cpp` files
1. Remember:
	1. Header guards
	1. Add appropriate `#include`s
	1. When done delete `stockvalue.h/.cpp`

1. Add a `virtual` destructor to `class Product`.  It does not need any logic `virtual ~Product() {}` is sufficient.  Add `sealed` to all classes that **don't** have a virtual destructor.

	***Question*** Should `Stock` and `Future` be `sealed`?  Why? Or why not?

