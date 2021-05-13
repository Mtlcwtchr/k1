#pragma once
#include <string>

class User
{
private:
	std::string username;
	std::string password;
	bool isAdmin;

public:
	User()
	{

	}

	User(std::string username, std::string password, bool isPromoted)
	{
		this->username = username;
		this->password = password;
		this->isAdmin = isPromoted;
	}

	std::string getUsername()
	{
		return username;
	}

	std::string getPassword()
	{
		return password;
	}

	bool isPromoted()
	{
		return isAdmin;
	}

	void setUsername(std::string username)
	{
		this->username = username;
	}

	void setPassword(std::string password)
	{
		this->password = password;
	}

	void setPromoted(bool isPromoted)
	{
		this->isAdmin = isPromoted;
	}

};

