#ifndef PORTFOLIO_INCLUDED
#define PORTFOLIO_INCLUDED

#include <memory>
#include <vector>

#include "DiscountPolicy.h"
#include "product.h"
namespace mallon::cpp
{
	// Declaration for DiscountPolicy
	struct DiscountPolicy;

	// The trivial version of Portfolio
	class Portfolio sealed
	{
		std::vector<Product*> products;

		std::unique_ptr<DiscountPolicy> discountPolicy;

	public:
		Portfolio() = default;
		Portfolio(const Portfolio& other);

		Portfolio& operator=(const Portfolio& right);

		void addProduct(Product* pProduct);

		double averageProductValue() const;

		void addDiscountPolicy(double discountPercentage, const std::string& reason);
		std::tuple<double, std::string> getDiscountPolicy();
	};
}
#endif
