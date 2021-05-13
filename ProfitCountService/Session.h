#pragma once
#include "User.h"

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

	void setUser(User* user);
};

