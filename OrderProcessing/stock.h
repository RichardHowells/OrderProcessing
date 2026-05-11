#pragma once
#include "product.h"

namespace mallon::cpp
{
	class Stock : public Product
	{

	public:
		Stock(std::string ticker, double price);

		double getValue(double quantity) const override;
	};
}
