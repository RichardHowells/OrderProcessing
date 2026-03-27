#include "stockvalue.h"

double getStockValue(double price, double quantity)
{
	auto stockValue = price * quantity;
	return stockValue;
}
