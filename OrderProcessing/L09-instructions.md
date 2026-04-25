## Resource management types

### Replace the raw pointer with `std::unique_ptr<>`

#### A resource management type can simplify your code

1. Take a quick count of how many lines of code in `portfolio.h` (35) and `portfolio.cpp` (80)
1. To support resource management we added a copy constructor, an `operator=`, and a destructor.  Remove all three.  (Don't mark them deleted, remove the code completely)
1. Replace the `DiscountPolicy` raw pointer with an `std::unique_ptr<DiscountPolicy>` (you'll need an `include`)
1. Replace the `new DiscountPolicy....` with a call to `std::make_unique<DiscountPolicy>`
1. Try to compile.  Discover that the attempts to copy and assign in OrderProcessing.cpp will not compile.  This is good because at least the type is safe; the raw pointer version was actively dangerous
1. Comment out the copy and assign attempts
1. Your code may still not compile.  If you see a message like "...can't delete an incomplete type..." this is because `unique_ptr` needs to see the full type declaration.  The forward declaration in `portfolio.h` is not sufficient, you will need the full `include`
1. Your code should now compile and run - notice that (again unlike the raw pointer) even with no programmer supplied  destructor there is no leak

	### Bonus ideas 

	#### Reinstate copy and assign
1. Reinstate the copy constructor declaration
1. Implement it in the .cpp file
	1. Copy **all** of the members, except the discount policy pointer, in the constructor initialization list.  Omit the discount policy pointer.  Its default constructor will set it to `nullptr`
	1. In the body, if the object being copied from has a non null discount policy pointer, use `std::make_unique` to create a **copy** of the pointer's target object, assign the result to `discountPolicy`.  
1. Reinstate the `operator=` declaration
1. Implement it in the .cpp file
	1. memberwise assign across each individual member, except the discount policy pointer
	1. test the parameter object's discount policy pointer.  If not == `nullptr` then use `std::make_unique` to create a copy of the target object.  Assign the result directly to `discountPoilicy`.  Else if equal to `nullptr` assign `nullptr` to `discountPolicy`
	1. There is no need to manually delete `discountPolicy`'s original target object.  `unique_ptr` will take care of that as you assign its new value 
1. In `OrderProcessing.cpp` uncomment the copy and assign lines.
1. Your code should run, as before, and without any leaks
1. How much smaller is your code? (`portfolio.cpp` is about 66 lines in the solution files)


