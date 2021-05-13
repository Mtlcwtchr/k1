#pragma once
#include <string>
#include <iostream>

class Command 
{
public:
	virtual void execute(std::string *args) = 0;
	virtual uint16_t requiredArgsCount() = 0;
	virtual std::string commandManual() = 0;

	static Command* of(std::string);
};

class AuthCommand : public Command
{
public:
	virtual void execute(std::string* args);
	virtual uint16_t requiredArgsCount();
	virtual std::string commandManual();
};

class RegCommand : public Command
{
public:
	virtual void execute(std::string* args);
	virtual uint16_t requiredArgsCount();
	virtual std::string commandManual();
};

class GetCommand : public Command
{
public:
	virtual void execute(std::string* args);
	virtual uint16_t requiredArgsCount();
	virtual std::string commandManual();
};

class GetAllCommand : public Command
{
public:
	virtual void execute(std::string* args);
	virtual uint16_t requiredArgsCount();
	virtual std::string commandManual();
};

class SaveCommand : public Command
{
public:
	virtual void execute(std::string* args);
	virtual uint16_t requiredArgsCount();
	virtual std::string commandManual();
};

class DelCommand : public Command
{
public:
	virtual void execute(std::string* args);
	virtual uint16_t requiredArgsCount();
	virtual std::string commandManual();
};

class GetProfitCommand : public Command
{
public:
	virtual void execute(std::string* args);
	virtual uint16_t requiredArgsCount();
	virtual std::string commandManual();
};

class BlankCommand : public Command
{
public:
	virtual void execute(std::string* args);
	virtual uint16_t requiredArgsCount();
	virtual std::string commandManual();
};

class BuyCommand : public Command
{
public:
	virtual void execute(std::string* args);
	virtual uint16_t requiredArgsCount();
	virtual std::string commandManual();
};

class MainInterface
{
private:

public:
	void deploy();
	
};

