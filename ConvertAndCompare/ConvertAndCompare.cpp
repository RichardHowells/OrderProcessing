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
};

int main()
{
	std::cout << "Hello World!\n";

	Experiment a{ 99 };
	a.display();
}

