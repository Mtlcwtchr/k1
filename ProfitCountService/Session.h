#pragma once
#include "User.h"
#include "MainInterface.h"

class Session
{
private:
	static Session* current;
	User* user = nullptr;


public:
	static Session* getCurrent();

	void tryAuth();
	bool isLogged();
	bool isPromoted();

	friend void AuthCommand::execute(std::string* args);
	friend void RegCommand::execute(std::string* args);
};

