## Dynamic memory

### Create a class to model a DiscountPolicy.  Have Portfolio manage an optional DiscountPolicy

#### Create the class skeleton

1. Add a file `DiscountPolicy.h`
1. Add the skeleton for a `struct DiscountPolicy`.  `struct DiscountPolicy` should be in the namespace `mallon::cpp`.  The difference between `class` and `struct` is that `struct`s default to `public` visibility,
1. Add a standard header guard to the file
1. Add a file `DiscountPolicy.cpp`.  For the skeleton class it has only the line `#include "DiscountPolicy.h"`

	#### Add a couple of fields 

1. Add a `double` member for `discountPercentage`, and an `std::string` for `reason`

	#### Use `DiscountPolicy` from `Portfolio`.  Having a `DiscountPolicy` is optional.  The `DiscountPolicy` is managed via a pointer.  If the pointer is null there is no discount policy.  Later we will introduce an inheritance hierarchy for different kinds of `DiscountPolicy`.  That hierarchy is best managed with a pointer.

1. In `Portfolio` declare a `DiscountPolicy` pointer, initialized to `nullptr`.  For this to compile you will be tempted to add an include for `DiscountPolicy.h`. The full include will work, but use a 'class (actually struct) declaration'.  It's not necessary to have the full include here.  In general it is a better practise to avoid the full include where you can. Full includes take more time in the compilation process. In really large C++ projects build time can become a serious issue.
	```C++
	struct DiscountPolicy;
	```

1. Add a member function `addDiscountPolicy` taking a `double discountPercentage` and an `std::string reason` as parameters
1. Implement it in the .cpp file to dynamically allocate a `DiscountPolicy` object initialized from the parameters.  Store the pointer in the `discountPercentage` member. You will need a full include for the header file
1. Add a member function `getDiscountPolicy`.  A discount policy has two data items, implement this function to return an `std::tuple<double, std::string>`.  Research the documentation for `std::tuple` to determine the required header file.  Further research the documentation for `std::make_tuple` to see how to return the two values packaged into a tuple

	#### Use the `DiscountPolicy` feature from `OrderProcessing.cpp`

1. In `OrderProcessing.cpp` locate one of the `Portfolio` objects
1. Call its `addDiscountPolicy` member.  Supply a couple of arbitrary parameter values
1. Call its `getDiscountPolicy` member.  Use the 'structured binding' syntax to unpack the tuple values into two separate variables.  Something like
	```C++
	const auto [discountPercentage, reason] = portfolio.getDiscountPolicy();
	```
1. Display the two variables and test your code to check that they are the same as originally passed to `addDiscountPolicy`
1. Test your program.  Notice that even with a memory leak it (appears to) work.  Here the leak is too small to cause noticeable damage

	#### Fix the memory leak

1. Declare a destructor in `class Portfolio`
1. Implement it in the .cpp file to `delete` the object `discountPolicy` points to
1. Your program should run as before, but without leaking memory

	### Bonus ideas

	#### Add a crude memory leak detector. The best way to leak detect a program is with external tools.  For example `valgrind` on linux.  We will implement a very simple tool to count the excess of `new`s over `delete`s
1. We can override the builtin mechanism behind the new/delete operators by providing our own `new/delete` functions.  This does not replace the operators, it replaces functions that are called by the operators.  Somewhat confusingly the functions have the same name as the operators.  Paste this code into `OrderProcessing.cpp` somewhere near the top of the file will be fine.  The functions **must be** in the global namespace. Between them these functions count the excess of `new`s over `delete`s
	```C++

	// Very crude leak checker.  Does NOT cover all cases
	// On entry to a block of code where new and delete should balance, set the allocationCount to 0
	// AFTER the block exits, check allocationCount.  If new/delete *do* balance, it should be zero

	unsigned long allocationCount{ 0 };

	void* operator new(std::size_t amount)
	{
		auto p = ::malloc(amount);

		++allocationCount;
		return p;
	}
	void operator delete(void* p)
	{
		--allocationCount;
		::free(p);
	}

	```
1. Identify the lines of code where the `Portfolio` objects are created and used.  Enclose those lines in braces (`{}`) to make them a nested block.  In C++ local objects declared in a block are destroyed at the end of the block.  At the head of the block reset the global variable `allocationCount` to zero.
1. Immediately after the closing `}` paste in this code...
	```C++
		if (allocationCount == 0)
			std::cout << "No obvious leaks\n";
		else
			std::cout << "Leaked " << allocationCount << " heap object(s)\n";

	```
1. Run your code.  Expect to see the message `"No obvious leaks"` - deliberately phrased as 'obvious' because this simple leak detection code does not cover all possibilities
1. Return to `class Portfolio` comment out the `delete discountPolicy;` statement in the destructor
1. Expect to see a 'leak' message.  Notice that it's not just one object leaked.  This is because the `std::string` used in `class Portfolio` itself uses dynamic memory.  When the `Portfolio` object is leaked, the resources used by `std::string` are also leaked
1. Reinstate the `delete` statement

