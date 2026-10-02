// DevelopToyVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "toy_vector.h"

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

class Person {
	std::string name;
public:
	Person(const std::string& name) : name{ name } {}
};

int main()
{
	{
		std::cout << "Hello World!\n";

        // Place your code to test toy_vector here.  Then you will get the limited leak checking

		toy_vector<int> v_int;

		v_int.push_back(99);
		std::cout << v_int.back() << "\n";

		v_int.push_back(50);
		v_int.push_back(101);

		std::cout << "Using a manual for loop\n";
		for (toy_vector<int>::const_iterator v_int_iterator = v_int.begin(); v_int_iterator != v_int.end(); ++v_int_iterator)
			std::cout << "   " << *v_int_iterator << "\n";



		std::cout << "Using a range for loop\n";
		for (auto item : v_int)
			std::cout << "   " << item << "\n";

		toy_vector<std::string> v_string;

		v_string.push_back("Hello world");

		std::cout << v_string.back() << "\n";

		v_string.push_back("Good morning!");

		toy_vector<std::string> v_string_copy{ v_string };

		std::cout << "Using a range for loop over the string(s)\n";
		for (auto item : v_string_copy)
			std::cout << "   " << item << "\n";

		// Will compile - once we remove the dependency on raw array/default constructor
		toy_vector<Person> v_person;

		v_person.push_back(Person("Fred"));

		// Create a fresh toy_vector<string> and assign it over an existing one...

		toy_vector<std::string> fresh_vector;
		fresh_vector.push_back("One");
		fresh_vector.push_back("Two");
		fresh_vector.push_back("Three");
		fresh_vector.push_back("Four");

		v_string = fresh_vector;

		std::cout << "Using a range for loop over the reassigned string(s)\n";
		for (auto item : v_string)
			std::cout << "   " << item << "\n";
	}

	if (allocationCount == 0)
		std::cout << "No obvious leaks\n";
	else
		std::cout << "Leaked " << allocationCount << " heap object(s)\n";

	std::cout << "Program completed successfully\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
