#ifndef PORTFOLIO_INCLUDED
#define PORTFOLIO_INCLUDED

#include "stockvalue.h"
namespace mallon::cpp
{
	// The trivial version of Portfolio
	class Portfolio
	{
		Stock* stock1{ nullptr };
		Stock* stock2{ nullptr };

	public:
		void addStock(Stock* pStock);

		double averageStockPrice() const;
	};
}
#endif
