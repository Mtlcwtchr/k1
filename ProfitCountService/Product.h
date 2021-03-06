#pragma once
#include <string>
#include <iostream>
#include "IProfitable.h"

struct Product : IProfitable
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

	double calcProfit()
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
		if (str.find(".") != std::string::npos)
		{
			prod->primaryCost = std::stof(str.substr(0, pos).replace(str.find("."), 1, ",").c_str());
		}
		else
		{
			prod->primaryCost = std::stof(str.substr(0, pos).c_str());
		}
		str.erase(0, pos + 1);

		pos = str.find(":");
		if (str.find(".") != std::string::npos)
		{
			prod->marketCost = std::stof(str.substr(0, pos).replace(str.find("."), 1, ",").c_str());
		} 
		else
		{
			prod->marketCost = std::stof(str.substr(0, pos).c_str());
		}
		str.erase(0, pos + 1);

		return prod;
	}
};