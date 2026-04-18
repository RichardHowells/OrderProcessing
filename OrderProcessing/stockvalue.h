
#include <string>
// You can nest namespaces in one statement
// Or by simple nesting (see the cpp file)
namespace mallon::cpp
{
	class Stock {
		std::string ticker;
		double price;

	public:
		void setPrice(double newPrice);
		double getPrice();

		void setTicker(std::string newTicker);
		std::string getTicker();

		double getStockValue(double quantity);
	};
}

