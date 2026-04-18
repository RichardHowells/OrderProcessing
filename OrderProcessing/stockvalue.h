
#include <string>
// You can nest namespaces in one statement
// Or by simple nesting (see the cpp file)
namespace mallon::cpp
{
	class Stock {
		std::string ticker;
		double price;

	public:
		Stock(std::string ticker, double price);

		void setPrice(double newPrice);
		double getPrice() const
		{
			return price;
		}

		void setTicker(std::string newTicker);
		std::string getTicker() const;

		double getStockValue(double quantity) const;
	};

	inline std::string Stock::getTicker() const
	{
		return ticker;
	}
}

