// OrderProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

double getValue(double price, double quantity)
{
	auto stockValue = price * quantity;
	return stockValue;
}

// overload
double getValue(double price)
{
	double stockValue = price * 100.0;
	return stockValue;
}



int main()
{
	std::cout << "Hello World!\n";

	std::cout << "getValue(10, 50) " << getValue(10, 50) << "\n";

	std::cout << "getValue(10) " << getValue(10) << "\n";

	std::cout << "Program completed successfully\n";
}
