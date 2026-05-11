#include "stock.h"

namespace mallon::cpp
{

	Stock::Stock(std::string ticker, double price) : Product{ ticker, price }
	{
	}

	double Stock::getValue(double quantity) const
	{
		auto stockValue = getPrice() * quantity;
		return stockValue;
	}

}