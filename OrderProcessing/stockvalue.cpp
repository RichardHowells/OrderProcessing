#include "stockvalue.h"

// You can nest namespaces via simple nesting
// or you can nest them in one statement (see the .h file)
namespace mallon
{
	namespace cpp
	{
		Product::Product(std::string ticker, double price) : ticker{ ticker }, price{ price }
		{
		}

		void Product::setPrice(double newPrice)
		{
			price = newPrice;
		}

		Stock::Stock(std::string ticker, double price) : Product{ ticker, price }
		{
		}

		double Stock::getValue(double quantity) const
		{
			auto stockValue = getPrice() * quantity;
			return stockValue;
		}

		Future::Future(std::string ticker, double price, double depreciation)
			: Product{ ticker, price }, depreciation{ depreciation }
		{
		}

		double Future::getValue(double quantity) const
		{
			auto stockValue = getPrice() * quantity * (1 - depreciation/100);
			return stockValue;
		}
	}
}