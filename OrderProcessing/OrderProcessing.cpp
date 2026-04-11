// OrderProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include <vector>

//double getStockValue(double price, double quantity = 100.0);
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
			greeting[i] = toupper(greeting[i]);	// Better practice
		}
	}

	cout << greeting << "\n";

	// Split the string up into 'word's' and add each word into a vector<string>
	// A 'word' is a contiguous sequence of non space characters

	vector<string> words;
	for (size_t i = 0; i < greeting.length();)	// Note - no change expression
	{
		if (greeting[i] == ' ' || !isalpha(greeting[i]))
		{
			// Hit a group of spaces/punctuators - just step over them
			while (i < greeting.length() && (greeting[i] == ' ' || !isalpha(greeting[i])))
				++i;
		}
		else
		{
			// Hit a word - a group of alphabetics
			// Capture it
			string word{ "" };
			while (i < greeting.length() && greeting[i] != ' ' && isalpha(greeting[i]))
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

	// The compiler *may* notice that this results in an infinite loop
	// On Visual C++ 2026 it's noted in the IDE, but requires enabling all warnings (-Wall) in the compiler
	//for (size_t i = words.size()-1; i >= 0; --i)
	//	cout << words[i] << "\n";

	// Call to mallon::cpp::getStockValue is inferred via the using statement at the top of the file
	std::cout << "getStockValue(10, 50) " << getStockValue(10, 50) << "\n";

	// Even with the using statement present, a fuly qualified call is still allowed
	std::cout << "getStockValue(10) " << mallon::cpp::getStockValue(10) << "\n";

	std::cout << "using a for loop\n";
	for (int i = 0; i < 10; ++i)
	{
		if (i % 2 == 0)
			std::cout << "getStockValue(" << i * 10 << ", 50) " << getStockValue(i * 10, 50) << "\n";
		else
			std::cout << "getStockValue(" << i * 20 << ", 50) " << getStockValue(i * 20, 50) << "\n";
	}

	std::cout << "using a while loop\n";
	int i{ 0 };
	while (i < 10)
	{
		switch (i % 2)
		{
		case 0:
			std::cout << "getStockValue(" << i * 10 << ", 50) " << getStockValue(i * 10, 50) << "\n";
			break;
		case 1: // Could use default here
			std::cout << "getStockValue(" << i * 20 << ", 50) " << getStockValue(i * 20, 50) << "\n";
			break;
		}
		++i;
	}

	std::cout << "Program completed successfully\n";
}
