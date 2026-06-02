#ifndef STOCKVALUE_H
#define STOCKVALUE_H

#include <string>
// You can nest namespaces in one statement
// Or by simple nesting (see the cpp file)
namespace mallon::cpp
{
	class Product
	{
		const std::string ticker;
		double price;

	public:
		Product(std::string ticker, double price);
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


	class Stock : public Product
	{

	public:
		Stock(std::string ticker, double price);

		double getValue(double quantity) const override;
	};


	class Future : public Product
	{
		double depreciation;

	public:
		Future(std::string ticker, double price, double depreciation);

		double getValue(double quantity) const override;
	};
}


#endif // !STOCKVALUE_H
