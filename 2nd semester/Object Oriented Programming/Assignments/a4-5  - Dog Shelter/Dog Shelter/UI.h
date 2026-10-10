#pragma once
#include "Dog.h"
#include "DynamicVector.h"
#include "Repo.h"
#include "Service.h"
#include <string>
#include <iostream>
#include <cctype>

class UI
{
private:
	Service& service; 
public:
	UI(Service& service);
	std::string toLower(const std::string& text);
	std::string strip(const std::string& text);
	int readInt(const std::string& message);
	void run();
	void printMiniMenu();
	void browseDogs(DynamicVector<Dog> dogs);
	void menuAdmin();
	void menuUser();
};

