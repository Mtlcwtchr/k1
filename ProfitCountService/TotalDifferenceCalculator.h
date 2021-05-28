#pragma once
#include "Product.h"
#include <list>

class TotalDifferenceCalculator
{
public:
	template <typename T> double calcTotalProfit(std::list<T*> profitable)
	{
		double totalProfit = 0;

		for (std::list<Product*>::iterator it = profitable.begin(); it != profitable.end(); ++it)
		{
			totalProfit += (*it)->calcProfit();
		}

		return totalProfit;
	}
};

