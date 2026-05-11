#include "portfolio.h"
#include "DiscountPolicy.h"

namespace mallon::cpp
{
	Portfolio::Portfolio(const Portfolio& other)
		:product1{ other.product1 }, product2{ other.product2 }
	{
		if (other.discountPolicy)
			discountPolicy = std::make_unique<DiscountPolicy>(*other.discountPolicy);
	}
	Portfolio& Portfolio::operator=(const Portfolio& right)
	{
		product1 = right.product2;
		product2 = right.product2;
		if (right.discountPolicy)
			discountPolicy = std::make_unique<DiscountPolicy>(*right.discountPolicy);
		else
			discountPolicy = nullptr;

		return *this;
	}
	void Portfolio::addProduct(Product* pStock)
	{
		if (product1 == nullptr)
			product1 = pStock;
		else
			product2 = pStock;
	}

	double Portfolio::averageProductValue() const
	{
		double totalValue = 0;
		int count = 0;

		// In C++ ANY non-zero evaluates to true.  This is equivalent to if (product1 != nullptr)
		// It's a very common idiom in both C and C++
		if (product1)
		{
			++count;
			totalValue += product1->getValue(1);
		}
		if (product2)
		{
			++count;
			totalValue += product2->getValue(1);
		}

		if (count == 0)
			return 0;
		else
			return totalValue / count;

	}

	void Portfolio::addDiscountPolicy(double discountPercentage, const std::string& reason)
	{
		discountPolicy = std::make_unique<DiscountPolicy>(discountPercentage, reason);
	}

	std::tuple<double, std::string> Portfolio::getDiscountPolicy()
	{
		return std::make_tuple(discountPolicy->percentDiscount, discountPolicy->reason);
	}

}