## Conversions and Comparisons

### Setup

1. Create a tiny class `Experiment`
	1. Give it an `std::string` member `content`
	1. Give is a member function `display` that writes a message to `stdout`, something like "The content is \{insert content\}\n"

1. Test that this works
	1. Create an `Experiment` object 
	1. Call its `display` function
	
	### Conversions
	
1. Add a function that expects an `Experiment` parameter
1. Try calling it with 99 see that the compiler objects
1. Add a parameter constructor to `Experiment` taking an `int`.  Store the incoming value in the `content` member

	**NOTE** You *should* do this in the initializer list

	**HINT** check out the `std::to_string()` function

1. See that the function call is now accepted.  The single parameter constructor gives a rule for converting integer values into `Experiment` objects, and the compiler deploys that rule here

1. Go back and mark the constructor `explicit`.  See that the function call is no longer accepted

1. Change the function call to explicitly create the `Experiment` object

	```C++
	f(Experiment{99});
	```

1. Add a function that expects an `int` parameter

1. Try calling it with an `Experiment` object
1. See that the compiler objects
1. Add to the `Experiment` class a conversion operator to convert to int
	```C++
	operator int ()
	{
		return stoi(content);
	}
1. See that the compiler will now deploy the `operator int` and the function call will compile

1. Because of the conversion operator a number of other things 'suddenly' become possible.  Add code to try out the full set of conversion operators. (Copy/paste this code - it **ASSUMES** that you have in scope `Experiment` objects named `a` and `b`
	```C++
	bool z = a == b;  
	bool y = a != b;  
	bool x = a < b;  
	bool w = a <= b;  
	bool v = a >= b;  
	bool u = a > b;  
	```
1.	See that all of them will compile.  The compiler converts to `int` and then the builtin `int` to `int` comparisons will work
1. Temporarily comment out the conversion operator and see that none of them will compile.
1. Reinstate the conversion operator

	### Comparisons - the STL requirements

1. Many STL algorithms require to compare objects in order to sequence them.  For example `std::sort`.  **many** of those algorithms are implemented using just `operator <`, **most** will be happy with `operator <` and `operator ==`

1. Create an `std::vector<Experiment>` and populate it with a few `Experiment` objects.  Copy/paste this code.  Notice that the objects are *deliberately* in a scrambled sequence
	```C++
	std::vector<Experiment> experiments{ Experiment{300}, Experiment{2000}, 
	Experiment{5}, Experiment{40},  Experiment{10000} };

	```

1. Add these lines to sort and print the vector

	```C++
		std::cout << "Sorted experiments\n";
		std::sort(experiments.begin(), experiments.end());
		for (auto e : experiments)
			e.display();
	```

1. Notice that the results are sorted in numeric ascending order.  The algorithm compares `Experiment` objects using `<`.  The compiler's only choice is to convert to `int` and then apply the builtin `int` comparison
1. Add an explicit `operator <` to `Experiment`.  Place this code inside the class
	```C++
	friend bool operator <(const Experiment& left, const Experiment& right) {
		return left.content < right.content;
	}
	```

1. Run and discover that the objects are now sorted according to string rules and appear in text ascending order.  The compiler finds that the explicit `operator <` is a better overload match than going via the conversion operator

1. Unfortunately this gives some suprises.  Add this code to the program...
	```C++
	// Surprising - if x < y == true then a normal human expects x > y to be false
	std::cout << "Is 10 < 2? " << (Experiment{ 10 } < Experiment{ 2 }) << "\n";
	std::cout << "Is 10 > 2? " << (Experiment{ 10 } > Experiment{ 2 }) << "\n";
	```
1. This is because for the `<` comparison the compiler will choose the friend function.  For the `>` comparison it will go via the conversion

	**NOTE** Best practice, if you supply one secondary comparison (<, \<=, >=, >) then you should supply them all

	## Bonus ideas

	### Spaceship - One Stop Shopping for Comparisons - (from C++ 20)

1. Remove (comment out) the `operator <` in `Experiment`
1. Add a three-way comparison operator to `Experiment`.  It should:
	1. Be a non-member function
	1. Be named `operator <=>`
	1. Take two `const Experiment &`s as parameters
	1. Return `std::strong_ordering`
	1. Be a `friend` so that it can access the non public members of `Experiment`
	1. Implement it using this code
	
	```C++
		if (left.content < right.content)
			return std::strong_ordering::less;
		else if (right.content < left.content)
			return std::strong_ordering::greater;
		else
			return std::strong_ordering::equal;
	```

1. Test your code.  You expect the sort to still produce text ascending values.  **AND** you expect the `<` `>` anomaly to be gone
	
	**NOTE** Implementing `operator <=>` implicitly implements **all** the secondary comparisons.  The compiler will prefer them over the conversion to `int` and builtin comparison

	**NOTE** All of the comparison operators in the code compile

1. This is potentially slower than it need be because it can require up to two calls to `std::string` comparison operators

1. `std::string` has its own operator \<=>.  Delegating directly to that requires only one string comparison.  Try it

1. In this example all the members (there is only one) participate in the comparison.  The compiler can automate generating that.  Try `default`ing the comparison.