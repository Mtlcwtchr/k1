#pragma once
#include <string>

struct Product
{
	std::string name;
	uint16_t amountBought;
	uint16_t amountSold;
	double primaryCost;
	double marketCost;

	Product()
	{

	}

	Product(std::string name, uint16_t amountBought, uint16_t amountSold, double primaryCost, double marketCost)
	{
		this->name = name;
		this->amountBought = amountBought;
		this->amountSold = amountSold;
		this->primaryCost = primaryCost;
		this->marketCost = marketCost;
	}

	float calcProfit()
	{
		return amountSold * marketCost - amountBought * primaryCost;
	}
};