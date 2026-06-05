#include "stockvalue.h"

double getValue(double price, double quantity)
{
	auto stockValue = price * quantity;
	return stockValue;
}
