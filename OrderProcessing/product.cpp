#include "product.h"

namespace mallon
{
	namespace cpp
	{
		Product::Product(std::string ticker, double price) : ticker{ ticker }, price{ price }
		{
		}
		void Product::setTicker(std::string newTicker)
		{
			ticker = newTicker;
		}

		void Product::setPrice(double newPrice)
		{
			price = newPrice;
		}
	}
}