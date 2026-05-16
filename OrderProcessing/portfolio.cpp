#include "portfolio.h"
#include "DiscountPolicy.h"

#include <numeric>

namespace mallon::cpp
{
	Portfolio::Portfolio(const Portfolio& other)
		:products{ other.products }
	{

		if (other.discountPolicy)
			discountPolicy = std::make_unique<DiscountPolicy>(*other.discountPolicy);
	}
	Portfolio& Portfolio::operator=(const Portfolio& right)
	{
		products = right.products;

		if (right.discountPolicy)
			discountPolicy = std::make_unique<DiscountPolicy>(*right.discountPolicy);
		else
			discountPolicy = nullptr;

		return *this;
	}
	void Portfolio::addProduct(Product* pStock)
	{
		products.push_back(pStock);
	}

	double Portfolio::averageProductValue() const
	{
		// size_t count = 0;
		// double totalValue = 0.0;
		//for (const auto& pProduct : products)
		//{
		//	++count;
		//	totalValue += pProduct->getValue(1);
		//}

		// Using iterators to navigate the collection
		//for (auto it = products.begin(); it != products.end(); ++it)
		//{
		//	++count;
		//	totalValue += (*it)->getValue(1);
		//}

		double totalValue = std::accumulate(products.begin(), products.end(), 0.0,
			[](auto runningTotal, const auto pObjectToAccumulate) { 
				return runningTotal + pObjectToAccumulate->getValue(1); });

		if (products.size() == 0)
			return 0;
		else
			return totalValue / products.size();

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