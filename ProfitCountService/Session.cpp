#include "Session.h"
#include "MainInterface.h"
#include "SmartPointer.hpp"
#include <iostream>
#include <string>

Session* Session::current = nullptr;

void Session::tryAuth()
{
	std::cout << "¬ведите auth чтобы войти или reg чтобы зарегистрироватьс€: " << std::endl;
	std::string str;
	cin >> str;
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

void Session::setUser(User* user)
{
	this->user = user;
}

Session* Session::getCurrent()
{
	if (!Session::current)
	{
		Session::current = new Session();
	}

	return Session::current;
}