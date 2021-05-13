#pragma once
#include "ProductRepository.h"
#include "Product.h"

class TotalDifferenceCalculator
{
public:
	float calcTotalProfit(std::list<Product*> products)
	{
		float totalProfit = 0;

		for (std::list<Product*>::iterator it = products.begin(); it != products.end(); ++it)
		{
			totalProfit += (*it)->calcProfit();
		}

		return totalProfit;
	}
};

