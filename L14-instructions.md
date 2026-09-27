## Selecting an Algorithm with Constraints

### Setup

**NOTE** This work is in the `OrderProcessing` project.  All the changes are in `OrderProcessing.cpp`

	### A simple copy_array function template

1. Add `#include <cstring>`, `#include <type_traits>` and `#include <concepts>` at the top of `OrderProcessing.cpp`

1. Above `main`, add a function template to copy the elements of one array into another array.  Use this signature
	```C++
	template <typename T>
	void copy_array(T* dest, const T* src, std::size_t count)
	```
1. Implement it with a `for` loop that assigns each element of `src` to the matching element of `dest`
1. At the start of the function write a message to `cout` so we can see which version was used.  Something like `"copy_array: element by element loop\n"`

1. Test it with an array of `int`.  Add this code near the end of `main`, just before the "Program completed successfully" message
	```C++
	int sourceInts[]{ 1, 2, 3, 4, 5 };
	int destInts[5]{};
	copy_array(destInts, sourceInts, std::size(sourceInts));
	```
1. Add a loop to print the contents of `destInts`, and check that they match `sourceInts`

	**NOTE** The compiler deduces `T` as `int` from the arguments.  There is no need to write `copy_array<int>(...)`

1. Test it with an array of `Portfolio`.  Copy/paste this code.  It gives each source `Portfolio` different contents
	```C++
	Portfolio sourcePortfolios[3];
	sourcePortfolios[0].addProduct(&apple);
	sourcePortfolios[1].addProduct(&microsoft);
	sourcePortfolios[2].addProduct(&apple);
	sourcePortfolios[2].addProduct(&google);
	sourcePortfolios[2].addDiscountPolicy(5, "Copied by copy_array");

	Portfolio destPortfolios[3];
	copy_array(destPortfolios, sourcePortfolios, std::size(sourcePortfolios));
	```
1. Add a loop to print `averageProductValue()` for each of the `destPortfolios`, and check that they match the source values.  Also print the discount policy from `destPortfolios[2]`

	**NOTE** The `dest[i] = src[i]` line in `copy_array` calls the `Portfolio::operator=` that you wrote in an earlier lab.  That is how each destination `Portfolio` gets its own copy of the `DiscountPolicy`

	### Why one algorithm is not always the best

1. For the `int` array the loop is correct, but a single call to `std::memcpy` would copy the whole block of memory at once.  For large arrays of simple types that is often faster
1. For the `Portfolio` array `std::memcpy` would be a disaster.  A `Portfolio` contains a `std::vector` and a `std::unique_ptr`, and both of them own heap memory.  A byte by byte copy would leave two objects both believing they own the same memory, and both would try to delete it
1. The standard library has a type trait that tells us when a byte by byte copy is safe: `std::is_trivially_copyable_v<T>`.  It is `true` for `int`.  It is `false` for `Portfolio`, because `Portfolio` has its own copy constructor and `operator=`
1. Check this for yourself.  Add these lines above `main`.  They are checked by the compiler; the program does not have to run
	```C++
	static_assert(std::is_trivially_copyable_v<int>);
	static_assert(!std::is_trivially_copyable_v<Portfolio>);
	```

	### Add a memcpy version, selected by a constraint

1. Add a second `copy_array` function template, just after the first one.  Give it **exactly** the same signature
1. Implement it with a single call to `std::memcpy`.  Remember that `memcpy` counts in bytes, not elements
	```C++
	std::memcpy(dest, src, count * sizeof(T));
	```
1. Write a different message to `cout`, something like `"copy_array: memcpy\n"`
1. Build.  The compiler objects that the function template has already been defined.  Two templates with the same signature are not allowed
1. Add a `requires` clause to the new template, between the `template` line and the function signature
	```C++
	template <typename T>
		requires std::is_trivially_copyable_v<T>
	void copy_array(T* dest, const T* src, std::size_t count)
	```
1. Build again.  The constraint is part of the template's signature, so the two templates are now different

1. Before running, predict which message you will see for the `int` array, and which for the `Portfolio` array
1. Run and check your prediction.  You should see:
	1. `memcpy` for the `int` array
	1. `element by element loop` for the `Portfolio` array
1. Check that the copied values are still correct for both arrays, and that the program still reports "No obvious leaks"

	**NOTE** How the compiler chooses:
	1. for `Portfolio` the constraint is not satisfied, so the `memcpy` version is removed from the list of candidates.  Only the loop version is left
	1. for `int` **both** versions are candidates.  The compiler prefers the constrained version, because it is more specific than the unconstrained one

	**NOTE** The selection happens entirely at compile time.  There is no `if` statement being evaluated when the program runs

	### Use named concepts

	#### A requires clause with a bare type trait works, but a named concept says what we mean

1. Add these two concepts above the `copy_array` templates
	```C++
	template <typename T>
	concept element_copyable = std::assignable_from<T&, const T&>;

	template <typename T>
	concept bitwise_copyable = element_copyable<T> && std::is_trivially_copyable_v<T>;
	```
1. Change the loop version to use the shorthand notation
	```C++
	template <element_copyable T>
	```
1. Change the `memcpy` version the same way, using `bitwise_copyable`, and remove its `requires` clause
1. Build and run.  The output should be exactly the same as before

	**NOTE** Now **both** templates are constrained, so why is the `memcpy` version still preferred for `int`?  Because `bitwise_copyable` is written in terms of `element_copyable`, the compiler can see that `bitwise_copyable` is the stricter of the two.  This is called *subsumption*.  It relies on both concepts sharing the same named check.  If each concept spelled out its own copy of a type trait expression, for example `std::is_copy_assignable_v<T>`, the compiler would treat the two copies as unrelated, and the call for `int` would be ambiguous

	### Bonus ideas

	#### See the error messages

1. Add this class above `main`.  It cannot be assigned
	```C++
	struct NoAssign {
		std::string name;
		NoAssign& operator=(const NoAssign&) = delete;
	};
	```
1. Try calling `copy_array` with two arrays of `NoAssign`.  Read the error message.  Notice that it points at **your call**, and it lists each concept that was not satisfied
1. Temporarily change the loop version back to a plain `template <typename T>`, with no constraint.  Read the error message again.  Notice that this time it points **inside** `copy_array`, at the `dest[i] = src[i]` line.  Which message would you rather receive?
1. Restore the constraint, and comment out the `NoAssign` test

	#### A trap in the type trait

1. Add this class.  It is just an `int` with the assignment removed
	```C++
	struct TrivialNoAssign {
		int value;
		TrivialNoAssign& operator=(const TrivialNoAssign&) = delete;
	};
	```
1. Add a `static_assert` to show that `std::is_trivially_copyable_v<TrivialNoAssign>` is `true`.  Surprising!  Its copy constructor is still trivial, and that is enough to make it trivially copyable
1. With the plain `requires std::is_trivially_copyable_v<T>` version, a call to `copy_array` with `TrivialNoAssign` arrays would compile, and would happily `memcpy` over objects that are not supposed to be assigned.  Our `bitwise_copyable` concept also requires `element_copyable`, so the call is rejected.  Try it

	#### Make the memcpy version safer

1. Passing a null pointer to `std::memcpy` is undefined behaviour, **even when** the count is zero.  Add a check so that `memcpy` is only called when `count` is not zero
1. `std::memcpy` must not be used when the source and destination overlap.  `std::memmove` is allowed to.  Look up `std::memmove` and consider whether to use it instead

	#### Compare with the standard library

1. Look up `std::copy`.  The library implementations do the same thing as your `copy_array`: they use `memmove` for trivially copyable types, and an element by element loop for everything else
1. Replace one of your `copy_array` calls with `std::copy(std::begin(src), std::end(src), std::begin(dest))`, and check that the result is the same
