#pragma once
#include "product.h"
#include <string>

namespace mallon::cpp
{
	class Future : public Product
	{
		double depreciation;

	public:
		Future(std::string ticker, double price, double depreciation);

		double getValue(double quantity) const override;
	};

}