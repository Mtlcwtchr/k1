#include "MainInterface.h"
#include "ProductRepository.h"
#include "AuthRepository.h"
#include "RepositoryType.h"
#include "TotalDifferenceCalculator.h"
#include "Session.h"
#include "SmartPointer.hpp"
#include <iostream>

using namespace dao;

Command* Command::of(std::string name) 
{
	Command* command = nullptr;
	int hash = std::hash<std::string>()(name);
	//std::cout << hash;
	switch (hash)
	{
	case 1410115415:
		command = new GetCommand();
		break;
	case -332427470:
		command = new GetAllCommand();
		break;
	case -1790990257:
		command = new AuthCommand();
		break;
	case 1140098453:
		command = new RegCommand();
		break;
	case -855671224:
		command = new SaveCommand();
		break;
	case -816214454:
		command = new DelCommand();
		break;
	case -1241294987:
		command = new GetProfitCommand();
		break;
	case 1708488555:
		command = new BuyCommand();
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
	return "Введите логин и пароль для входа, разделяя данные пробелом или клавишей return: ";
}

void RegCommand::execute(std::string* args)
{
	std::string uname = ((std::string*)args)[0];
	std::string pass = ((std::string*)args)[1];

	SmartPointer<AuthRepository>* repo = new SmartPointer<AuthRepository>(AuthRepository::of(RepositoryType::TXT));

	Session::getCurrent()->user = (*repo)->tryAuth(uname, pass);
}

uint16_t RegCommand::requiredArgsCount()
{
	return 2;
}

std::string RegCommand::commandManual()
{
	return "Введите логин и пароль для регистрации пользователя, разделяя данные пробелом или клавишей return: ";
}

void GetCommand::execute(std::string* args)
{
	std::string name = ((std::string*)args)[0];
	
	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	Product* product = (*repo)->get(name);

	if (product)
	{
		std::cout << "Продукт с указанным именем найден: " << std::endl;
		std::cout << "Имя продукта: " << product->name << '\t' << "Закуплено: " << product->amountBought << '\t' << "Продано: " << product->amountSold << '\t' << "Цена закупки: " << product->primaryCost << '\t' << "Выходная цена: " << product->marketCost << std::endl;
	}
	else
	{
		std::cout << "Продукт с указанным именем не найден" << std::endl;
	}

}

uint16_t GetCommand::requiredArgsCount()
{
	return 1;
}

std::string GetCommand::commandManual()
{
	return "Введите название продукции, информацию о которой необходимо вывести: ";
}

void GetAllCommand::execute(std::string* args)
{
	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	std::list<Product*> products = (*repo)->get();

	uint8_t sortMode = std::atoi(args[0].c_str());
	switch (sortMode)
	{
	case 1:
		products.sort([](const auto& o1, const auto& o2) -> bool {
			return 1;
		});
	case 2:
		products.sort([](const auto& o1, const auto& o2) -> bool {
			return o1->amountBought - o2->amountBought;
			});
		break;
	case 3:
		products.sort([](const auto& o1, const auto& o2) -> bool {
			return o1->amountSold - o2->amountSold;
			});
		break;
	case 4:
		products.sort([](const auto& o1, const auto& o2) -> bool {
			return o1->primaryCost - o2->primaryCost;
			});
		break;
	case 5:
		products.sort([](const auto& o1, const auto& o2) -> bool {
			return o1->marketCost - o2->marketCost;
			});
		break;
	default:
		break;
	}

	std::cout << "Список продуктов: " << std::endl;
	for (std::list<Product*>::iterator it = products.begin(); it != products.end(); ++it)
	{
		auto i = *it;
		std::cout << "Имя продукта: " << i->name << '\t' << "Закуплено: " << i->amountBought << '\t' << "Продано: " << i->amountSold << '\t' << "Цена закупки: " << i->primaryCost << '\t' << "Выходная цена: " << i->marketCost << std::endl;
	}
}

uint16_t GetAllCommand::requiredArgsCount()
{
	return 1;
}

std::string GetAllCommand::commandManual()
{
	return "Введите 1 для сортировки по имени продукта, 2 - для сортировки по размерам закупки, 3 - для сортировки по размерам продаж, 4 - по цене закупки, 5 - по цене продажи";
}

void DelCommand::execute(std::string* args)
{
	if (!Session::getCurrent()->isPromoted())
	{
		std::cout << "Доступ запрещен " << std::endl;
		return;
	}

	std::string name = ((std::string*)args)[0];

	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	(*repo)->del(name);

	std::cout << "Продукт успешно удален" << std::endl;
}

uint16_t DelCommand::requiredArgsCount()
{
	return 1;
}

std::string DelCommand::commandManual()
{
	return "Введите название продукта, подлежащего удалению. Для получения списка продуктов введите команду \'getall\'";
}

void SaveCommand::execute(std::string* args)
{
	if (!Session::getCurrent()->isPromoted())
	{
		std::cout << "Доступ запрещен " << std::endl;
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
		std::cout << "Продукт успешно сохранен: " << std::endl;
		std::cout << "Имя продукта: " << product->name << '\t' << "Закуплено: " << product->amountBought << '\t' << "Продано: " << product->amountSold << '\t' << "Цена закупки: " << product->primaryCost << '\t' << "Выходная цена: " << product->marketCost << std::endl;
	}
	else
	{
		std::cout << "Не удалось сохранить продукт" << std::endl;
	}
}

uint16_t SaveCommand::requiredArgsCount()
{
	return 5;
}

std::string SaveCommand::commandManual()
{
	return "Введите имя продукта, количество закупки, размер продаж продукта, цену закупки и цену продажи продукта, разделяя данные пробелом или клавишей return\n Учтите, что при введении имени уже существующего в базе продукта его значения перезапишутся вместо создания нового продукта";
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
			std::cout << "Извините, продукции недостаточно для совершения покупки, всего осталось: " << prod->amountBought - prod->amountSold << std::endl;
			return;
		}
		else
		{
			prod->amountSold = totalSold;
			prod = (*repo)->save(prod);

			if (prod)
			{
				std::cout << "Продукт успешно приобретен" << std::endl;
			}
			else
			{
				std::cout << "Не удалось приобрести продукт" << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Продукт не найден" << std::endl;
	}
}

uint16_t BuyCommand::requiredArgsCount()
{
	return 2;
}

std::string BuyCommand::commandManual()
{
	return "Введите имя продукта и размер закупки";
}

void GetProfitCommand::execute(std::string* args)
{
	if (!Session::getCurrent()->isPromoted())
	{
		std::cout << "Доступ запрещен " << std::endl;
		return;
	}

	SmartPointer<ProductRepository>* repo = new SmartPointer<ProductRepository>(ProductRepository::of(RepositoryType::TXT));
	std::list<Product*> products = (*repo)->get();

	float totalProfit = (new TotalDifferenceCalculator())->calcTotalProfit(products);

	std::cout << "Итоговая выручка составляет: " << totalProfit << std::endl;
}

uint16_t GetProfitCommand::requiredArgsCount()
{
	return 0;
}

std::string GetProfitCommand::commandManual()
{
	return "Пользовательский ввод не требуется";
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
				std::cout << "Данный пользователь уже существует" << std::endl;
				break;
			case 303:
				std::cout << "Неверный логин или пароль" << std::endl;
				break;
			case 404:
				std::cout << "Невозможно провести авторизацию" << std::endl;
				break;
			default:
				break;
			}
		}
	}

	std::cout << "Вы вошли в систему\n" << std::endl;

	std::cout << "Список команд для ввода: \n" << "getall - вывод списка всех продуктов\n" << "get - вывод конкретного продукта по имени\n" << "getprofit - вывод итоговой прибыли, необходимы права администратора\n" << "buy - приобретение продукта по имени\n" << "save - сохранение или изменение продукта, необходимы права администратора\n" << "del - удаление существующего продукта по имени, необходимы права администратора\n" << "exit - завершение работы\n";

	while (true)
	{
		std::string str;
		std::cin >> str;
		if (str == "exit")
		{
			break;
		}

		SmartPointer<Command>* command = new SmartPointer<Command>(Command::of(str));
		if (command)
		{
			uint16_t requiredArgsCount = (*command)->requiredArgsCount();
			std::string* args = new std::string[requiredArgsCount];
			if (requiredArgsCount > 0)
			{
				std::cout << (*command)->commandManual() << std::endl;
				for (int i = 0; i < requiredArgsCount; ++i)
				{
					std::cin >> args[i];
				}
				std::cout << "Спасибо, данные приняты" << std::endl;
			}
			(*command)->execute(args);
		}
	}
}