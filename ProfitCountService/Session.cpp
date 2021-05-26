#include "Session.h"
#include "MainInterface.h"
#include "SmartPointer.hpp"
#include <iostream>
#include <string>

Session* Session::current = nullptr;

void Session::tryAuth()
{
	std::string str;
	do
	{
		std::cout << "¬ведите 0 чтобы войти или 10 чтобы зарегистрироватьс€: " << std::endl;
		cin >> str;
	} while (str != "0" && str != "10");

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
				std::cin >> args[i];
			}
		}
		(*command)->execute(args);
	}
}

bool Session::isPromoted()
{
	return user != nullptr && user->isPromoted();
}

bool Session::isLogged()
{
	return user != nullptr;
}

Session* Session::getCurrent()
{
	if (!Session::current)
	{
		Session::current = new Session();
	}

	return Session::current;
}