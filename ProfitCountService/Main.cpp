#pragma once

#include <list>
#include <windows.h>
#include "MainInterface.h"


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	MainInterface* main = new MainInterface();
	main->deploy();

	return 0;
}