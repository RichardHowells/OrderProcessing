#include "portfolio.h"
#include "DiscountPolicy.h"

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
		double totalValue = 0;
		int count = 0;

		//for (const auto& pProduct : products)
		//{
		//	++count;
		//	totalValue += pProduct->getValue(1);
		//}

		// Using iterators to navigate the collection
		for (auto it = products.begin(); it != products.end(); ++it)
		{
			++count;
			totalValue += (*it)->getValue(1);
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