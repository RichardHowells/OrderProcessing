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

