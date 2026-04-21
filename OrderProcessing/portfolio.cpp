#include "portfolio.h"
#include "DiscountPolicy.h"

namespace mallon::cpp
{
	void Portfolio::addStock(Stock* pStock) 
	{
		if (stock1 == nullptr)
			stock1 = pStock;
		else
			stock2 = pStock;
	}

	double Portfolio::averageStockPrice() const
	{ 
		double totalValue = 0;
		int count = 0;

		// In C++ ANY non-zero evaluates to true.  This is equivalent to if (stock1 != nullptr)
		// It's a very common idiom in both C and C++
		if (stock1)
		{
			++count;
			totalValue += stock1->getPrice();
		}
		if (stock2)
		{
			++count;
			totalValue += stock2->getPrice();
		}

		if (count == 0)
			return 0;
		else
			return totalValue / count;

	}

	void Portfolio::addDiscountPolicy(double discountPercentage, const std::string& reason)
	{
		discountPolicy = new DiscountPolicy(discountPercentage, reason);
	}

	std::tuple<double, std::string> Portfolio::getDiscountPolicy() 
	{
		return std::make_tuple(discountPolicy->percentDiscount, discountPolicy->reason);
	}

}