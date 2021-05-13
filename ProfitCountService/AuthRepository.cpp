#include "AuthRepository.h"
#include "User.h"
#include <fstream>
#include <iostream>

TxtAuthRepository::TxtAuthRepository(std::string sourcepath)
{
	this->sourcepath = sourcepath;
}

User* TxtAuthRepository::tryAuth(std::string uname, std::string pass)
{
	std::ifstream in;
	in.open(sourcepath, std::ios::in);

	if (!in) {
		throw 404;
	}

	std::string username;
	std::string password;
	bool isPromoted;

	while (!in.eof())
	{
		in >> username >> password >> isPromoted;
		if (username == uname)
		{
			if (std::atoi(password.c_str()) == std::hash<std::string>()(pass))
			{
				return new User(uname, pass, isPromoted);
			}
		}
	}

	throw 303;
}

User* TxtAuthRepository::tryRegister(std::string uname, std::string pass)
{
	std::ifstream in;
	in.open(sourcepath, std::ios::in);

	if (!in) {
		throw 404;
	}

	std::string username;
	std::string password;
	bool isPromoted;

	while (!in.eof())
	{
		in >> username >> password >> isPromoted;
		if (username == uname)
		{
			throw 302;
		}
	}

	std::ofstream out;
	out.open(sourcepath, std::ios::app);

	if (!out) {
		throw 404;
	}

	out << uname << '\t' << std::hash<std::string>()(pass) << '\t' << 0;

	return new User(username, password, false);
}

AuthRepository* AuthRepository::of(RepositoryType type)
{
	{
		AuthRepository* repo = nullptr;
		switch (type)
		{
		case TXT:
			repo = new TxtAuthRepository("auth.txt");
			break;
		default:
			break;
		}

		return repo;
	}
}