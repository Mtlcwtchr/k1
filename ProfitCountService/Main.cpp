#pragma once

#include <list>
#include "MainInterface.h"


int main() {
	setlocale(LC_ALL, "Russian");

	MainInterface* main = new MainInterface();
	main->deploy();

	return 0;
}