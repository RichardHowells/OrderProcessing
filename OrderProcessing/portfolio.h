#ifndef PORTFOLIO_INCLUDED
#define PORTFOLIO_INCLUDED

#include <tuple>

#include <memory>

#include "DiscountPolicy.h"
#include "stockvalue.h"
namespace mallon::cpp
{
	// Declaration for DiscountPolicy
	struct DiscountPolicy;

	// The trivial version of Portfolio
	class Portfolio
	{
		Stock* stock1{ nullptr };
		Stock* stock2{ nullptr };

		std::unique_ptr<DiscountPolicy> discountPolicy;

	public:
		Portfolio() = default;

		void addStock(Stock* pStock);

		double averageStockPrice() const;

		void addDiscountPolicy(double discountPercentage, const std::string& reason);
		std::tuple<double, std::string> getDiscountPolicy();
	};
}
#endif
