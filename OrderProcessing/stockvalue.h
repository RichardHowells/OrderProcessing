#ifndef STOCKVALUE_H
#define STOCKVALUE_H

#include <string>
// You can nest namespaces in one statement
// Or by simple nesting (see the cpp file)
namespace mallon::cpp
{
	class Stock {
		const std::string ticker;
		double price;

	public:
		Stock(std::string ticker, double price);

		void setPrice(double newPrice);
		double getPrice() const
		{
			return price;
		}

		std::string getTicker() const;

		double getValue(double quantity) const;
	};

	inline std::string Stock::getTicker() const
	{
		return ticker;
	}
}


#endif // !STOCKVALUE_H
