// OrderProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

//double getValue(double price, double quantity = 100.0);
#include "stockvalue.h"
#include "stockvalue.h"
#include "portfolio.h"

// Very crude leak checker.  Does NOT cover all cases
// On entry to a block of code where new and delete should balance, set the allocationCount to 0
// AFTER the block exits, check allocationCount.  If new/delete *do* balance, it should be zero
unsigned long allocationCount{ 0 };

void* operator new(std::size_t amount)
{
	auto p = ::malloc(amount);

	++allocationCount;
	return p;
}
void operator delete(void* p)
{
	--allocationCount;
	::free(p);
}

using namespace mallon::cpp;
using namespace std;

void comparePortfolios(const Portfolio& p1, const Portfolio& p2)
{
	std::cout << "Passed by const reference, ";
	if (p1.averageStockPrice() < p2.averageStockPrice())
		std::cout << "p2 has the highest average cost\n";
	else if (p1.averageStockPrice() == p2.averageStockPrice())
		std::cout << "p1 and p2 have equal average cost\n";
	else
		std::cout << "p1 has the highest average cost\n";
}

void comparePortfolios(const Portfolio* p1, const Portfolio* p2)
{
	std::cout << "Passed by const *, ";
	if (p1->averageStockPrice() < p2->averageStockPrice())
		std::cout << "p2 has the highest average cost\n";
	else if (p1->averageStockPrice() == p2->averageStockPrice())
		std::cout << "p1 and p2 have equal average cost\n";
	else
		std::cout << "p1 has the highest average cost\n";
}

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
	// A 'word' is a contiguous sequence of alphabetic characters

	vector<string> words;
	for (size_t i = 0; i < greeting.length();)	// Note - no change expression
	{
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
		cout << words[i - 1] << "\n";

	// Your compiler *may* notice that this results in an infinite loop
	// On Visual C++ 2026 it's noticed in the IDE, but requires enabling all warnings (-Wall) in the compiler
	//for (size_t i = words.size()-1; i >= 0; --i)
	//	cout << words[i] << "\n";

	// Set the double to output in fixed point with two digits after the decimal point
	std::cout << fixed << setprecision(2);


	// mallon::cpp::Stock is inferred via the using statement at the top of the file
	Stock apple{ "AAPL", 50 };

	std::cout << "apple.getValue(10) " << apple.getValue(10) << "\n";

	// Even with the using statement present, a fully qualified name is still allowed
	mallon::cpp::Stock microsoft{ "MSFT",75 };

	std::cout << "microsoft.getValue(10) " << microsoft.getValue(10) << "\n";

	Future google{ "GOOG", 100, 10 };
	std::cout << "google.getValue(10) " << google.getValue(10) << "\n";

	Product* productPointer;

	// Polymorphic calls via a pointer
	productPointer = &apple;
	std::cout << productPointer->getTicker() << ".getValue(10) (via a base class pointer) " << productPointer->getValue(10) << "\n";

	productPointer = &google;
	std::cout << productPointer->getTicker() << ".getValue(10) (via a base class pointer) " << productPointer->getValue(10) << "\n";

	// Polymorphic calls via a reference - for references it works better when they are function parameters
	// because an ordinary reference as a variable has to be intialized and cannot be rebound
	
	Product& appleRef = apple;
	std::cout << appleRef.getTicker() << ".getValue(10) (via a base class reference) " << appleRef.getValue(10) << "\n";

	Product& googleRef = google;
	std::cout << googleRef.getTicker() << ".getValue(10) (via a base class reference) " << googleRef.getValue(10) << "\n";



	std::cout << "using a for loop with apple\n";
	for (int i = 0; i < 10; ++i)
	{
		if (i % 2 == 0)
			std::cout << "apple.getValue(" << setw(3) << i * 10 << ") " << setw(7) << apple.getValue(i * 10) << "\n";
		else
			std::cout << "apple.getValue(" << setw(3) << i * 20 << ") " << setw(7) << apple.getValue(i * 20) << "\n";
	}

	std::cout << "using a while loop with microsoft\n";
	int i{ 0 };
	while (i < 10)
	{
		switch (i % 2)
		{
		case 0:
			std::cout << "microsoft.getValue(" << setw(3) << i * 10 << ") " << setw(7) << microsoft.getValue(i * 10) << "\n";
			break;
		case 1: // Could use default here
			std::cout << "microsoft.getValue(" << setw(3) << i * 20 << ") " << setw(7) << microsoft.getValue(i * 20) << "\n";
			break;
		}
		++i;
	}

	{
		::allocationCount = 0;
		Portfolio portfolio;
		std::cout << "Average price for empty portfolio " << portfolio.averageStockPrice() << "\n";

		portfolio.addProduct(&apple);
		std::cout << "Average price for apple only portfolio " << portfolio.averageStockPrice() << "\n";

		portfolio.addProduct(&microsoft);
		std::cout << "Average price for apple + microsoft portfolio " << portfolio.averageStockPrice() << "\n";

		Portfolio portfolio2;
		comparePortfolios(portfolio, portfolio2);
		comparePortfolios(portfolio2, portfolio);
		comparePortfolios(portfolio, portfolio);

		comparePortfolios(&portfolio, &portfolio2);
		comparePortfolios(&portfolio2, &portfolio);
		comparePortfolios(&portfolio, &portfolio);

		portfolio.addDiscountPolicy(10, "This is a good customer");

		const auto [discountPercentage, reason] = portfolio.getDiscountPolicy();
		std::cout << "Discount " << discountPercentage << " reason " << reason << "\n";

		Portfolio portfolio3{ portfolio2 };
		Portfolio portfolio4{ portfolio };
		const auto [discountPercentage4, reason4] = portfolio4.getDiscountPolicy();
		std::cout << "From portfolio4 - Discount " << discountPercentage4 << " reason " << reason4 << "\n";


		Portfolio portfolio5;
		portfolio5.addDiscountPolicy(25, "To demonstrate a leak");
		portfolio5 = portfolio;
		const auto [discountPercentage5, reason5] = portfolio5.getDiscountPolicy();
		std::cout << "From portfolio5 - Discount " << discountPercentage5 << " reason " << reason5 << "\n";

		Portfolio portfolio6;
		portfolio6.addProduct(&google);
		std::cout << "Average price for Google only portfolio " << portfolio6.averageStockPrice() << "\n";

	}
	if (allocationCount == 0)
		std::cout << "No obvious leaks\n";
	else
		std::cout << "Leaked " << allocationCount << " heap object(s)\n";

	std::cout << "Program completed successfully\n";
}
