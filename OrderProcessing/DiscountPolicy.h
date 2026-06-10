#ifndef DISCOUNTPOLICY_H
#define DISCOUNTPOLICY_H

#include <string>

namespace mallon::cpp
{
	struct DiscountPolicy sealed
	{
		double percentDiscount{ 0 };
		std::string reason;
	};
}
#endif // !DISCOUNTPOLICY_H
