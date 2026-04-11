## Standard Collections - string and vector

### Using `std::string` and `std::vector`
1. Working in the `OrderProcessing.cpp` file
	### Using `std::string`
1. Create a `std::string` named `greeting` initialize it to `"Hello C++ student"` 
1. Display it on cout.  Emit a new line afterwards to make the output move to a new line
1. Use simple concatenation (`+`) to append `", it is a fine day today."`
1. Display it on `cout`
1. Use the plus-assign operator (`+=`) to append `" We should study C++!"`

	### Strings are indexable and mutable
	#### Convert the vowels to uppercase
1. Write a loop to index through each character of the string

	**NOTE** Think about what might be the best type to use to index into the string

1. If a character is a lowercase vowel (i.e. a,e,i,o, or u) overwrite it with its upper case equivalent
	
	**Hint** - research `toupper()` in the docs. Pay special attention to including the correct header file.  It is sometimes possible that a header file brings in other, not directly related, declarations.  It's a bad practice to rely on that behaviour.

	**Warning** `toupper()` is fundamentally a C language function and has an ASCII biased view of the world.  When presented with accented and other characters it can give unexpected results.  See the docs for details.

1. Display the string on `cout`
	### Using `std::vector`
	#### Split the string into words and print the words in reverse order

	**WARNING** - this can be quite tricky to get right

1. Use a very simple definition of a 'word' as a group of contiguous non-space characters
1. Create an empty `vector<string>` named `words`
1. Iterate over the string characters
1. Identify groups of pure spaces and ignore them
1. Identify groups of non-blank characters.  Capture each character into a temporary string
1. At the end of a word group, append (`push_back()`) the temporary into the `words` vector
1. Print the words in the vector in reverse order. **WARNING** - using `size_t` is an excellent practice, using `auto` is an even better practice.  With either you must be extremely careful **NEVER** to generate a negative number.  `size_t` cannot represent negative numbers
	### Bonus ideas
1. Temporarily change the type of the one of the loop control variables to `int`.  Does your compiler give you any warning messages? (***note this behaviour will be compiler dependent.  The compiler is not obliged to give ANY message***)

	`int` (typically) cannot hold the full range of possible return values from `vector::size()`.  There is a risk with a very large vector (over about 2 billion items) that `int` cannot correctly represent the length

1. Examine how your compiler behaves if `size_t` is presented with a negative value.  As an example from the solution code this could be done by changing the loop that traverses the words vector backwards from this...
	```C++
		for (size_t i = words.size(); i > 0; --i)
			cout << words[i-1] << "\n";
	```
	...to this...
	```C++
		for (size_t i = words.size()-1; i >= 0; --i)
			cout << words[i] << "\n";
	```
	Superficially these two codes are identical.  But the second version relies on `i` becoming less than zero, specifically `-1`, which `size_t` cannot represent.  ***A compiler might give a diagnostic that the loop will run forever.***


1. Modify your program so that a word is considered to be a group of alphabetic characters only.  Punctuation characters and numbers should be ignored. ***Hint - research the `isalpha()` function.  It also has an ASCII biased view of the world***

	