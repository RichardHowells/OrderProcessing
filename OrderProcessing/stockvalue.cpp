#include "stockvalue.h"

// You can nest namespaces via simple nesting
// or you can nest them in one statement (see the .h file)
namespace mallon
{
	namespace cpp
	{
		double getStockValue(double price, double quantity)
		{
			auto stockValue = price * quantity;
			return stockValue;
		}
	}
}