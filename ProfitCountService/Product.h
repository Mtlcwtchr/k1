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
		name = "";
		amountBought = 0;
		amountSold = 0;
		primaryCost = 0;
		marketCost = 0;
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

	static Product* fromString(std::string str)
	{
		Product* prod = new Product();
		size_t pos = str.find(":");
		prod->name = str.substr(0, pos);
		str.erase(0, pos + 1);

		pos = str.find(":");
		prod->amountBought = std::atoi(str.substr(0, pos).c_str());
		str.erase(0, pos + 1);


		pos = str.find(":");
		prod->amountSold = std::atoi(str.substr(0, pos).c_str());
		str.erase(0, pos + 1);


		pos = str.find(":");
		prod->primaryCost = std::atof(str.substr(0, pos).c_str());
		str.erase(0, pos + 1);

		pos = str.find(":");
		prod->marketCost = std::atof(str.substr(0, pos).c_str());
		str.erase(0, pos + 1);

		return prod;
	}
};