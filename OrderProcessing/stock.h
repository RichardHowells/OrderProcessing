#pragma once
#include "product.h"
#include <memory>

namespace mallon::cpp
{
	class Stock : public Product
	{

	public:
		Stock(std::string ticker, double price);

		double getValue(double quantity) const override;
	};
}
