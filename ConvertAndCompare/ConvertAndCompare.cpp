// ConvertAndCompare.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <format>

class Experiment
{
	int number;

public:
	Experiment(int number) : number{ number } {}

	void display()
	{
		std::cout << "The number is " << number << "\n";
	}

	std::string toString() {
		return std::format("{}", number);
	}
};

int main()
{
	std::cout << "Hello World!\n";

	Experiment a{ 99 };
	a.display();
	std::cout << a.toString() << "\n";

	Experiment b{ 99 };


	// bool z = a == b;  will not compile
	// bool y = a < b;
	// bool x = a > b;

}

