#include "stockvalue.h"

// You can nest namespaces via simple nesting
// or you can nest them in one statement (see the .h file)
namespace mallon
{
	namespace cpp
	{
		Stock::Stock(std::string ticker, double price) : ticker{ ticker }, price{ price }
		{
		}

		void Stock::setPrice(double newPrice)
		{
			price = newPrice;
		}

		double Stock::getValue(double quantity) const
		{
			auto stockValue = price * quantity;
			return stockValue;
		}
	}
}