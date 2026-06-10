#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
namespace mallon::cpp
{
	class Product
	{
		std::string ticker;
		double price;

	public:
		Product(std::string ticker, double price);
		virtual ~Product() {}
		void setTicker(std::string newTicker);
		std::string getTicker() const;

		void setPrice(double newPrice);
		double getPrice() const
		{
			return price;
		}

		virtual double getValue(double quantity) const = 0;

	};

	inline std::string Product::getTicker() const
	{
		return ticker;
	}
}
#endif

