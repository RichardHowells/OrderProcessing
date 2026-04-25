#ifndef PORTFOLIO_INCLUDED
#define PORTFOLIO_INCLUDED

#include <tuple>

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

		DiscountPolicy* discountPolicy{ nullptr };

	public:
		Portfolio() = default;
		~Portfolio();
		//Portfolio(const Portfolio& other) = delete;
		Portfolio(const Portfolio& other);
		//Portfolio& operator=(const Portfolio& other) = delete;
		Portfolio& operator=(const Portfolio& other);

		void addStock(Stock* pStock);

		double averageStockPrice() const;

		void addDiscountPolicy(double discountPercentage, const std::string& reason);
		std::tuple<double, std::string> getDiscountPolicy();
	};
}
#endif
