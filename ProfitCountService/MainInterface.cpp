#include "MainInterface.h"
#include "ProductRepository.h"
#include "AuthRepository.h"
#include "RepositoryType.h"
#include "TotalDifferenceCalculator.h"
#include "Session.h"
#include "SmartPointer.hpp"
#include <iostream>
#include <algorithm>

using namespace dao;

Command* Command::of(uint16_t code) 
{
	Command* command = nullptr;
	switch (code)
	{
	case 2:
		command = new GetCommand();
		break;
	case 1:
		command = new GetAllCommand();
		break;
	case 0:
		command = new AuthCommand();
		break;
	case 10:
		command = new RegCommand();
		break;
	case 5:
		command = new SaveCommand();
		break;
	case 6:
		command = new DelCommand();
		break;
	case 3:
		command = new GetProfitCommand();
		break;
	case 4:
		command = new BuyCommand();
		break;
	case 7:
		command = new GetAllFilteredCommand();
		break;
	default:
		command = new BlankCommand();
		break;
	}
	return command;
}

void AuthCommand::execute(std::string* args) 
{
	std::string uname = ((std::string*)args)[0];
	std::string pass = ((std::string*)args)[1];

	SmartPointer<AuthRepository>* repo = new SmartPointer<AuthRepository>(AuthRepository::of(RepositoryType::TXT));

	Session::getCurrent()->user = (*repo)->tryAuth(uname, pass);
}

uint16_t AuthCommand::requiredArgsCount()
{
	return 2;
}

std::string AuthCommand::commandManual()
{
	return "������� ����� � ������ ��� �����, �������� ������ �������� ��� �������� return: ";
}

void RegCommand::execute(std::string* args)
{
	std::string uname = ((std::string*)args)[0];
	std::string pass = ((std::string*)args)[1];


	SmartPointer<AuthRepository>* repo = new SmartPointer<AuthRepository>(AuthRepository::of(RepositoryType::TXT));

	Session::getCurrent()->user = (*repo)->tryRegister(uname, pass);
}

uint16_t RegCommand::requiredArgsCount()
{
	return 2;
}

std::string RegCommand::commandManual()
{
	return "������� ����� � ������ ��� ����������� ������������, �������� ������ �������� ��� �������� return: ";
}

void GetCommand::execute(std::string* args)
{
	std::string name = ((std::string*)args)[0];
	
	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	Product* product = (*repo)->get(name);

	if (product)
	{
		std::cout << "������� � ��������� ������ ������: " << std::endl;
		std::cout << "��� ��������: " << product->name << '\t' << "���������: " << product->amountBought << '\t' << "�������: " << product->amountSold << '\t' << "���� �������: " << product->primaryCost << '\t' << "�������� ����: " << product->marketCost << std::endl;
	}
	else
	{
		std::cout << "������� � ��������� ������ �� ������" << std::endl;
	}

}

uint16_t GetCommand::requiredArgsCount()
{
	return 1;
}

std::string GetCommand::commandManual()
{
	return "������� �������� ���������, ���������� � ������� ���������� �������: ";
}

void GetAllCommand::execute(std::string* args)
{
	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	std::list<Product*> products = (*repo)->get();

	uint8_t sortMode = std::atoi(args[0].c_str());
	switch (sortMode)
	{
	case 1:
		products.sort([](Product* a, Product* b) -> bool {
			return (a->name.compare(b->name) < 0);
		});
		break;
	case 2:
		products.sort([](Product* a, Product* b) -> bool {
			return a->amountBought > b->amountBought;
		});
		break;
	case 3:
		products.sort([](Product* a, Product* b) -> bool {
			return a->amountSold > b->amountSold;
		});
		break;
	case 4:
		products.sort([](Product* a, Product* b) -> bool {
			return a->primaryCost > b->primaryCost;
		});
		break;
	case 5:
		products.sort([](Product* a, Product* b) -> bool {
			return a->marketCost > b->marketCost;
		});
		break;
	default:
		break;
	}

	std::cout << "������ ���������: " << std::endl;
	for (std::list<Product*>::iterator it = products.begin(); it != products.end(); ++it)
	{
		auto i = *it;
		std::cout << "��� ��������: " << i->name << '\t' << "���������: " << i->amountBought << '\t' << "�������: " << i->amountSold << '\t' << "���� �������: " << i->primaryCost << '\t' << "�������� ����: " << i->marketCost << std::endl;
	}
}

uint16_t GetAllCommand::requiredArgsCount()
{
	return 1;
}

std::string GetAllCommand::commandManual()
{
	return "������� 1 ��� ���������� �� ����� ��������, 2 - ��� ���������� �� �������� �������, 3 - ��� ���������� �� �������� ������, 4 - �� ���� �������, 5 - �� ���� �������";
}


void GetAllFilteredCommand::execute(std::string* args)
{
	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	std::list<Product*> products = (*repo)->get();

	double minMarketCost = std::stof(args[0].c_str());

	std::cout << "������ ��������� � ����� ������� ������ " << args[0] << ": " << std::endl;
	for (std::list<Product*>::iterator it = products.begin(); it != products.end(); ++it)
	{
		auto i = *it;
		if (i->marketCost >= minMarketCost) 
		{
			std::cout << "��� ��������: " << i->name << '\t' << "���������: " << i->amountBought << '\t' << "�������: " << i->amountSold << '\t' << "���� �������: " << i->primaryCost << '\t' << "�������� ����: " << i->marketCost << std::endl;
		}
	}
}

uint16_t GetAllFilteredCommand::requiredArgsCount()
{
	return 1;
}

std::string GetAllFilteredCommand::commandManual()
{
	return "������� ��������� �������� ���� ������� ��������.";
}


void DelCommand::execute(std::string* args)
{
	if (!Session::getCurrent()->isPromoted())
	{
		std::cout << "������ �������� " << std::endl;
		return;
	}

	std::string name = ((std::string*)args)[0];

	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	(*repo)->del(name);

	std::cout << "������� ������� ������" << std::endl;
}

uint16_t DelCommand::requiredArgsCount()
{
	return 1;
}

std::string DelCommand::commandManual()
{
	return "������� �������� ��������, ����������� ��������. ��� ��������� ������ ��������� ������� ����� \'1\'";
}

void SaveCommand::execute(std::string* args)
{
	if (!Session::getCurrent()->isPromoted())
	{
		std::cout << "������ �������� " << std::endl;
		return;
	}

	std::string name = ((std::string*)args)[0];
	std::string am1 = ((std::string*)args)[1];
	std::string am2 = ((std::string*)args)[2];
	std::string cost1 = ((std::string*)args)[3];
	std::string cost2 = ((std::string*)args)[4];

	Product* prod = new Product(name, atoi(am1.c_str()), atoi(am2.c_str()), atof(cost1.c_str()), atof(cost2.c_str()));

	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	Product* product = (*repo)->save(prod);

	if (product)
	{
		std::cout << "������� ������� ��������: " << std::endl;
		std::cout << "��� ��������: " << product->name << '\t' << "���������: " << product->amountBought << '\t' << "�������: " << product->amountSold << '\t' << "���� �������: " << product->primaryCost << '\t' << "�������� ����: " << product->marketCost << std::endl;
	}
	else
	{
		std::cout << "�� ������� ��������� �������" << std::endl;
	}
}

uint16_t SaveCommand::requiredArgsCount()
{
	return 5;
}

std::string SaveCommand::commandManual()
{
	return "������� ��� ��������, ���������� �������, ������ ������ ��������, ���� ������� � ���� ������� ��������, �������� ������ �������� return\n ������, ��� ��� �������� ����� ��� ������������� � ���� �������� ��� �������� ������������� ������ �������� ������ ��������";
}

void BuyCommand::execute(std::string* args)
{
	std::string name = ((std::string*)args)[0];
	std::string am1 = ((std::string*)args)[1];

	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	Product* prod = (*repo)->get(name);
	if (prod)
	{
		uint16_t totalSold = prod->amountSold + std::atoi(am1.c_str());
		if (totalSold > prod->amountBought) 
		{
			std::cout << "��������, ��������� ������������ ��� ���������� �������, ����� ��������: " << prod->amountBought - prod->amountSold << std::endl;
			return;
		}
		else
		{
			prod->amountSold = totalSold;
			prod = (*repo)->save(prod);

			if (prod)
			{
				std::cout << "������� ������� ����������" << std::endl;
			}
			else
			{
				std::cout << "�� ������� ���������� �������" << std::endl;
			}
		}
	}
	else
	{
		std::cout << "������� �� ������" << std::endl;
	}
}

uint16_t BuyCommand::requiredArgsCount()
{
	return 2;
}

std::string BuyCommand::commandManual()
{
	return "������� ��� �������� � ������ �������";
}

void GetProfitCommand::execute(std::string* args)
{
	if (!Session::getCurrent()->isPromoted())
	{
		std::cout << "������ �������� " << std::endl;
		return;
	}

	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	std::list<Product*> products = (*repo)->get();

	float totalProfit = (new TotalDifferenceCalculator())->calcTotalProfit(products);

	std::cout << "�������� ������� ����������: " << totalProfit << std::endl;
}

uint16_t GetProfitCommand::requiredArgsCount()
{
	return 0;
}

std::string GetProfitCommand::commandManual()
{
	return "���������������� ���� �� ���������";
}

void BlankCommand::execute(std::string* args)
{

}

uint16_t BlankCommand::requiredArgsCount()
{
	return 0;
}

std::string BlankCommand::commandManual()
{
	return "";
}

void MainInterface::deploy()
{
	while (!Session::getCurrent()->isLogged())
	{
		try
		{
			Session::getCurrent()->tryAuth();
		}
		catch (int errorCode)
		{
			switch (errorCode)
			{
			case 302:
				std::cout << "������ ������������ ��� ����������" << std::endl;
				break;
			case 303:
				std::cout << "�������� ����� ��� ������" << std::endl;
				break;
			case 404:
				std::cout << "���������� �������� �����������" << std::endl;
				break;
			default:
				break;
			}
		}
	}

	std::cout << "�� ����� � �������\n" << std::endl;

	if (Session::getCurrent()->isPromoted()) 
	{
		std::cout << "������ ������ ��� �����: \n" << "1 - ����� ������ ���� ���������\n" << "2 - ����� ����������� �������� �� �����\n" << "3 - ����� �������� �������, ���������� ����� ��������������\n" << "5 - ���������� ��� ��������� ��������, ���������� ����� ��������������\n" << "6 - �������� ������������� �������� �� �����, ���������� ����� ��������������\n" << "7 - ����� ��������� � ����� ������� ���� ���������\n" << "exit - ���������� ������\n";
	}
	else
	{
		std::cout << "������ ������ ��� �����: \n" << "1 - ����� ������ ���� ���������\n" << "2 - ����� ����������� �������� �� �����\n" << "4 - ������������ �������� �� �����\n" << "7 - ����� ��������� � ����� ������� ���� ���������\n" << "exit - ���������� ������\n";
	}
	
	while (true)
	{
		std::string str;
		do
		{
			std::cin >> str;

			if (str == "exit")
			{
				return;
			}

		} while (str != "1" && str != "2" && str != "3" && str != "4" && str != "5" && str != "6" && str != "7");

		SmartPointer<Command>* command = new SmartPointer<Command>(Command::of(atoi(str.c_str())));
		if (command)
		{
			uint16_t requiredArgsCount = (*command)->requiredArgsCount();
			std::string* args = new std::string[requiredArgsCount];
			if (requiredArgsCount > 0)
			{
				std::cout << (*command)->commandManual() << std::endl;
				for (int i = 0; i < requiredArgsCount; ++i)
				{	
					std::cin >> ws;
					std::getline(std::cin, args[i]);
				}
				std::cout << "�������, ������ �������" << std::endl;
			}
			(*command)->execute(args);
		}
	}
}