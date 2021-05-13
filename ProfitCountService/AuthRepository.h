#pragma once
#include <string>
#include "RepositoryType.h"
#include "User.h"

class AuthRepository
{
public:
	static AuthRepository* of(RepositoryType type);

	virtual User* tryAuth(std::string, std::string) = 0;
	virtual User* tryRegister(std::string, std::string) = 0;
};

class TxtAuthRepository : public AuthRepository
{
private:
	std::string sourcepath;

public:
	TxtAuthRepository(std::string sourcepath);

	virtual User* tryAuth(std::string, std::string);
	virtual User* tryRegister(std::string, std::string);
};