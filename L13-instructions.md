## Resource Management

### To develop a cut-down version of the library vector class

### Setup

**NOTE** This work is in the directory `DevelopToyVector`

1. Add a `template<typename T> class toy_vector`, in its own header file complete with header guards
	1. it should contain an array of 20 T
	1. it should have an int to track the first free element in the array
	1. it should have a `void push_back(const T& newValue)` function that stores its argument value in the first free element of the array.  Assume there will always be free space in the array. Update the first free element int
	1. it should have a `T& back()` function to return the last data item in the array

1. Add some lines of test code in `DevelopToyVector.cpp` to show that the `push_back` and `back` functions work correctly
1. Be sure to test `toy_vector` with both a predefined type (`int`) and a class type (`std::string`)

	### Show that toy_vector only works with default constructible types

1. Add (copy/paste) this simple `class Person`.  It has no default constructor
	```C++
	class Person {
		std::string name;
	public:
		Person(const std::string& name) : name{ name } {}
	};
	```
1. Try to define a `toy_vector<Person>`.  Discover that the embedded array demands that its elements be default constructible
1. Comment out that definition

	### Add loop support

	#### The data is stored in an array, therefore a pointer is a suitable iterator

1. Inside `class toy_vector` Add a type alias (`using`) making `iterator` an alias for `T*`; and `const_iterator` an alias for `const T *`.  This improves `toy_vector`'s compatibility with the library container conventions
1. Add a function `iterator begin()`.  It returns the address of the first element of the array
1. Add a function `iterator end()`.  It returns the address of the first free element in the array.  **note** this also follows the library convention of `end()` identifying a place ***one beyond*** the last actual data item.
1. Overload `begin`/`end` so that for a `const toy_vector` they return `const_iterator`

1. In `DevelopToyVector.cpp` add a manual for loop to iterate over a `toy_vector` and print each element.  Somthing like this...

	```C++
		std::cout << "Using a manual for loop\n";
		for (toy_vector<int>::const_iterator v_int_iterator = v_int.begin();
				v_int_iterator != v_int.end(); ++v_int_iterator)
			std::cout << "   " << *v_int_iterator << "\n";
	```

1. Repeat using the range `for` loop...

	```C++
		std::cout << "Using a range for loop\n";
		for (auto item : v_int)
			std::cout << "   " << item << "\n";
	```
	**NOTE** Following the library container conventions for `begin()`/`end()` allows `toy_vector` to work with range `for`

	### Make toy_vector storage dynamic (though still fixed size)

1. Replace the array member with a `T* data_start`
1. Adjust the constructor to allocate memory dynamically for the array
1. Replace the `int first_available` with a pointer (`T* first_available`)
1. Adjust the constructor to set `first_available` to the start of the memory block
1. `data_start` is an owning pointer. Add a destructor to delete the dynamic array.  For safety `= delete` the copy constructor and `operator=`
1. Adjust the other member functions to accomodate working with the dynamic array through pointers rather than the embedded array

	**NOTE** Implementing an automatically expanding `toy_vector` is left to the reader.  If you want to tackle this; do it later on after class.  You'd need to:
	1. in `push_back()` Detect overflowing the array 
	1. allocate a new, larger, array
	1. copy all the existing entries to the new array
	1. discard the old array


	### Use an allocator object

	#### This will also remove the requirement for default constructible elements

1. Extend the template types to include an `allocator`.  Have that default to `std::allocator<T>`
	```C++
	template <typename T, typename allocator = std::allocator<T>>
	```
1. Store an `allocator` by value in the class
1. Add a data member `T* limit` to point to just after the end of the allocated block of memory
1. Adjust the constructor such that:
	1. instead of `new T[20]` to allocate the memory block, call `allocator.allocate(20)`
	1. `first_available` should point to the start of the allocated memory block
	1. `limit` should point to `data_start + 20`

1. Adjust `push_back` to use `std::construct_at(first_available, newItem)` ***(look it up in the docs)***.  This constructs the incoming new object at a specified place in the allocated memory block

1. Adjust the `destructor` such that:
	1. remove the `delete []` operation
	1. iterate over the actual entries in the memory block; destroy each one by explicitly calling the destructor (`item->~T()`) for each one.  To be really fancy do it in reverse order because that's how `delete` does it
	1. unlike `delete` you are not allowed to pass `nullptr` to `allocator.deallocate`.  So check for `data_start` being not null then release the memory block by calling `allocator.deallocate(data_start, ...no of entries in the memory block...)`
	1. calculate the number of entries in the block as `limit - data_start`

	**NOTE** The allocator returns raw uninitialized memory.  Therefore contained type no longer needs to be default constructible.  This should be enough to allow defining a `toy_vector<Person>`.  Try it.

	### Implement copying and assign

	#### These apply the same approach as we used in earlier labs.  So just copy/paste this code...

	```C++
	toy_vector(const toy_vector& other) 
		: allocator{ other.allocator }, 
			data_start{ allocator.allocate(20) }, 
			first_available{ data_start }, 
			limit{ data_start + 20 }
		{
			std::uninitialized_copy(other.data_start, other.data_start + other.size(), first_available);
			first_available += other.size();
		}


		// Much simpler assignment - exploit the copy constructor
		toy_vector& operator=(const toy_vector& rhs)
		{
			auto copyOfRhsObject(rhs);

			// Potentially throwing operations completed

			// Now swap all of the internals with those of the copied object
			// which will destroy at the end of this function
			// except the allocator object these are just pointers.  They will swap very quickly

			// Bring std::swap into scope
			using std::swap;

			swap(allocator, copyOfRhsObject.allocator);
			swap(data_start, copyOfRhsObject.data_start);
			swap(first_available, copyOfRhsObject.first_available);
			swap(limit, copyOfRhsObject.limit);

			return *this;
		}

	```

1. Back in `DevelopToyVector.cpp` 
1. Add test code to define a new `toy_vector` as initialized as a copy of an existing one.  Check that the copy has the same content
1. Add test code to assign a `toy_vector` over an existing one.  Check that the freshly assigned object has the same content

	#### Implement move constructor

	**Note** the job of the move constructor is to steal resources from the moved from object, and leave it in a valid state.  The moved from object needs to be at least safe for destruction

1. Add the signature for the move constructor
	```C++
		toy_vector(toy_vector && other)
	```

1. In the initializer list grab ALL the data items from the incoming (`other`) object
1. In the body of the constructor assign `nullptr` to all the pointers
1. Back in `DevelopToyVector.cpp` add somthing like this...
	```C++
		toy_vector<Person> newVector { std::move(existingVector) };
	```
	The `std::move` is just a cast from `toy_vector<Person>` to `toy_vector<Person> &&`.  After the cast the compiler will prefer the move constructor overload.

1. Add code to confirm that the `newVector` contains all the data of the `existingVector`
1. We should not do much with `existingVector`. After moving from an object we know very little about its state.  Here we can check that `size()` returns zero, because we know what the move constuctor does


	### Bonus ideas

	#### Implement move assignment

1. Add the signature for move assignment
	```C++
		// Move assignment
		toy_vector& operator=(toy_vector&& rhs) noexcept
		{
		}
	```

1. Inside the function swap every data member with its counterpart in the parameter object

	### Implement a non-member `swap` function

1. The set of `swap` calls in the move assignment and the copy assignment, are duplicated code.  There is a standard approach here.  Factor them out into a **non-member** `swap` function.  This function requires access to non-public members of the class and therefore should be a friend.  This is most easy to implement directly in the class.  Use the signature...
	```C++
		friend void swap(toy_vector& left, toy_vector& right)
		{
		}
	```

	... implement the function to swap the internals of `left` and `right`. Call it from both overloads of `operator =`

	**NOTE** It is a good practice for programmer defined types to offer a non-member `swap` function.  This function then becomes a `swap` overload available to standard library routines that need to move around `toy_vector` objects.  It is assumed that an overload specific to `toy_vector` objects can make a better job of it than the more general purpose `std::swap` template. 

1. Your code should work unchanged

