#include "future.h"
namespace mallon::cpp
{
	Future::Future(std::string ticker, double price, double depreciation)
		: Product{ ticker, price }, depreciation{ depreciation }
	{
	}

	double Future::getValue(double quantity) const
	{
		auto stockValue = getPrice() * quantity * (1 - depreciation / 100);
		return stockValue;
	}
}