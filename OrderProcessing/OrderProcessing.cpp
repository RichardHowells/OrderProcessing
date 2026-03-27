// OrderProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

auto getStockValue(double price, double quantity = 100.0)
{
	auto stockValue = price * quantity;
	return stockValue;
}


int main()
{
	std::cout << "Hello World!\n";

	std::cout << "getStockValue(10, 50) " << getStockValue(10, 50) << "\n";

	std::cout << "getStockValue(10) " << getStockValue(10) << "\n";

	std::cout << "Program completed successfully\n";
}
