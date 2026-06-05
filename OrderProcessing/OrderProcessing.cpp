// OrderProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

//double getValue(double price, double quantity = 100.0);
#include "stockvalue.h"



int main()
{
	std::cout << "Hello World!\n";

	std::cout << "getValue(10, 50) " << getValue(10, 50) << '\n';

	std::cout << "getValue(10) " << getValue(10) << '\n';

	std::cout << "using a for loop\n";
	for (int i = 0; i < 10; ++i)
	{
		if (i % 2 == 0)
			std::cout << "getValue(" << i * 10 << ", 50) " << getValue(i * 10, 50) << "\n";
		else
			std::cout << "getValue(" << i * 20 << ", 50) " << getValue(i * 20, 50) << "\n";
	}

	std::cout << "Program completed successfully\n";
}
