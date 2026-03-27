// OrderProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

//double getStockValue(double price, double quantity = 100.0);
#include "stockvalue.h"


int main()
{
	std::cout << "Hello World!\n";

	std::cout << "getStockValue(10, 50) " << getStockValue(10, 50) << "\n";

	std::cout << "getStockValue(10) " << getStockValue(10) << "\n";

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
//
//double getStockValue(double price, double quantity)
//{
//	auto stockValue = price * quantity;
//	return stockValue;
//}
