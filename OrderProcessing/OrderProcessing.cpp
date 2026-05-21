// OrderProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstddef>

//double getValue(double price, double quantity = 100.0);
#include "stockvalue.h"

using namespace mallon::cpp;
using namespace std;

int main()
{
	std::cout << "Hello World!\n";

	string greeting{ "Hello c++ student" };
	cout << greeting << "\n";

	greeting = greeting + ", it is a fine day today.";

	greeting += " We should study C++!";
	cout << greeting << "\n";

	// C++ strings are mutable
	for (size_t i = 0; i < greeting.length(); ++i)
	{
		if (greeting[i] == 'a' || greeting[i] == 'e' || greeting[i] == 'i' || greeting[i] == 'o' || greeting[i] == 'u')
		{
			greeting[i] += 'A' - 'a';		// This is a very C style trick but you may see it in existing code

			// The library function std::toupper is better practice. BUT is only defined for ASCII characters
			// Anyone using a character set outside ASCII can run into undefined behaviour with raw uase of toupper
			// This convoluted expression is a safe way to use it.
			greeting[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(greeting[i])));	// Better practice
		}
	}

	cout << greeting << "\n";

	// Split the string up into 'word's' and add each word into a vector<string>
	// A 'word' is a contiguous sequence of alphabetic characters

	vector<string> words;
	for (size_t i = 0; i < greeting.length();)	// Note - no change expression
	{
		// Like toupper (mentioned above) isalpha is only defined for ASCII characters.
		// It should have the same protection.  For clarity that has not been dine in this
		// section of code
		if (!isalpha(greeting[i]))
		{
			// Hit a group of spaces/punctuators - just step over them
			while (i < greeting.length() && (!isalpha(greeting[i])))
				++i;
		}
		else
		{
			// Hit a word - a group of alphabetics
			// Capture it
			string word{ "" };
			while (i < greeting.length() && isalpha(greeting[i]))
			{
				word += greeting[i];
				++i;
			}
			// Add the word to the vector
			words.push_back(word);
		}
	}

	// Need to be REALLY careful in this loop. size_t cannot handle negative values
	// Must NOT generate a negative value in it
	cout << "Print the words in reverse order\n";
	for (size_t i = words.size(); i > 0; --i)
		cout << words[i-1] << "\n";

	// Your compiler *may* notice that this results in an infinite loop
	//for (size_t i = words.size()-1; i >= 0; --i)
	//	cout << words[i] << "\n";

	// Set the double to output in fixed point with two digits after the decimal point
	std::cout << fixed << setprecision(2);


	// mallon::cpp::Stock is inferred via the using statement at the top of the file
	Stock apple;
	apple.setTicker("AAPL");
	apple.setPrice(50);

	std::cout << "apple.getValue(10) " << apple.getValue(10) << '\n';

	// Even with the using statement present, a fully qualified name is still allowed
	mallon::cpp::Stock microsoft;
	microsoft.setTicker("MSFT");
	microsoft.setPrice(75);

	std::cout << "microsoft.getValue(10) " << microsoft.getValue(10) << "\n";

	std::cout << "using a for loop with apple\n";
	for (int i = 0; i < 10; ++i)
	{
		if (i % 2 == 0)
			std::cout << "apple.getValue(" << setw(3) << i * 10 << ") " << setw(7) << apple.getValue(i * 10) << '\n';
		else
			std::cout << "apple.getValue(" << setw(3) << i * 20 << ") " << setw(7) << apple.getValue(i * 20) << '\n';
	}

	std::cout << "using a while loop with microsoft\n";
	int i{ 0 };
	while (i < 10)
	{
		switch (i % 2)
		{
		case 0:
			std::cout << "microsoft.getValue(" << setw(3) << i * 10 << ") " << setw(7) << microsoft.getValue(i * 10) << '\n';
			break;
		case 1: // Could use default here
			std::cout << "microsoft.getValue(" << setw(3) << i * 20 << ") " << setw(7) << microsoft.getValue(i * 20) << '\n';
			break;
		}
		++i;
	}

	std::cout << "Program completed successfully\n";
}
