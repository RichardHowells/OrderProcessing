## Copying, and assignment

### Try copying a `Portfolio` object with a `DiscountPolicy`

1. Working in `OrderProcessing.cpp`. **INSIDE** the nested block, just before the end is a good place, create a copy of the `Portfolio` object that has no `DiscountPolicy`
1. Your code should run as before
1. Also inside the nested block, create a copy of the `Portfolio` object that does have a `DiscountPolicy`
	```C++
	Portfolio portfolio4{ portfolio };
	```
1. Your code should now crash/misbehave in some way.  It's caused by the two objects fighting over the same `DiscountPolicy` object and ultimately double deleting it as the objects go out of the block's scope

1. Comment out the copies
	#### Try assigning a `Portfolio` object with a `DiscountPolicy`
	```C++
	Portfolio portfolio5;
	portfolio5 = portfolio;
	```
1. Expect your code to crash in much the same way as the copy code did

	#### The compiler written copy and assign operations are dangerous in a type that owns resources.  The `Portfolio` type 'owns' the `DiscountPolicy` and mis-manages it

1. declare the copy constructor and the operator=; mark both as deleted
1. See that the assign operation will not compile
1. Uncomment the copy operations and see that they will not compile either
1. Discover that this **also** makes the compiler withdraw the complier supplied default constructor
1. Add a programmer written default constructor to `Portfolio`.  It is sufficient to `default` it
1. Discover that now attempts to copy or assign `Portfolio` objects are now flagged as errors by the compiler
1. Comment out the copy and assign statements
 

	#### Implement a deep copy constructor
1. Change the deleted copy constructor into a declaration
1. Implement it in the .cpp file
	1. Copy **all** of the members, except the discount policy pointer, in the constructor initialization list set the discount policy pointer to `nullptr`
	1. In the body, if the object being copied from has a non null discount policy pointer, create a **copy** of the pointer's target object
1. In `OrderProcessing.cpp` uncomment the copy lines
1. Your program should run cleanly with no reported leaks 
1. You should print the values from the copy's `DiscountPolicy` to check that it is a faithful copy

	### Bonus idea

	#### implement a copy assignment operator
1. Change the deleted `operator=` into a declaration
1. Implement it in the .cpp file.  You should:
	1. test the parameter object's discount policy pointer.  If not == `nullptr` then create a copy of the target object
	1. hold the pointer to the freshly copied object in a local temporary pointer.  Else hold `nullptr` in that local temporary
	1. memberwise assign across each individual member, except the discount policy pointer
	1. assign the discount policy pointer from the local temporary
1. Test at this stage (uncomment the assignment in `OrderProcessing.cpp`) and discover that you have a leak.  If you don't see the leak add an assignment that assigns **to** a `Portfolio` with a `DiscountPolicy`
1. Return to `Portfolio::operator=` before assigning to the discount policy pointer, delete the object it points to
1. Retest and expect to see that the leak is gone
1. You should print the values from the copy's `DiscountPolicy` to check that it is a faithful copy

