## Program Organisation

### Using std::string and std::vector
1. Working in the `OrderProcessing.cpp` file
	### Using std::string
1. Create a `std::string` named `greeting` initialize it to `"Hello C++ student"` 
1. Display it on cout.  Emit a new line afterwards to make the output move to a new line
1. Use simple concatenation (`+`) to append `", it is a fine day today."`
1. Display it on `cout`
1. Use the plus-assign operator (`+=`) to append `" We should study C++!"`

	### Strings are indexable and mutable
1. Write a loop to index through each character of the list
1. If a character is a lowercase vowel (ie. a,e,i,o, or u) overwrite it with it's upper case equivalent
	
	Hint - research `toupper`
1. Display the string on `cout`
	### Using std::vector
	#### Split the string into words and print the words in reverse order
1. **WARNING** - this can be quite tricky to get right
1. Use a very simple definition of a 'word' as a group of contiguous non-space characters
1. Create an empty `vector<string>` named `words`
1. Iterate over the string characters
1. Identify groups of pure spaces and ignore them
1. Identify groups of non-blank characters.  Capture each character into a temporary string
1. At the end of a word group, append (`push_back`) the temporary into the `words` vector
1. Print the words in the vector in reverse order. **WARNING** - using `size_t` is a good practice, but you must be extremly careful NEVER to generate a negative number.  Size_t cannot work with negative numbers.