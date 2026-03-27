// OrderProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

double getStockValue(double price, double quantity)
{
	double stockValue = price * quantity;
	return stockValue;
}

// overload
double getStockValue(double price)
{
	double stockValue = price * 100.0;
	return stockValue;
}



int main()
{
	std::cout << "Hello World!\n";

	std::cout << "getStockValue(10, 50) " << getStockValue(10, 50) << "\n";

	std::cout << "getStockValue(10) " << getStockValue(10) << "\n";

	std::cout << "Program completed successfully\n";
}
