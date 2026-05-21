#include "stockvalue.h"

// You can nest namespaces via simple nesting
// or you can nest them in one statement (see the .h file)
namespace mallon
{
	namespace cpp
	{
		void Stock::setPrice(double newPrice)
		{
			price = newPrice;
		}

		double Stock::getPrice()
		{
			return price;
		}

		void Stock::setTicker(std::string newTicker)
		{
			ticker = newTicker;
		}

		std::string Stock::getTicker() 
		{
			return ticker;
		}

		double Stock::getValue(double quantity)
		{
			auto stockValue = price * quantity;
			return stockValue;
		}
	}
}