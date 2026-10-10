#pragma once
#include "Dog.h"
#include <vector>
#include <algorithm>
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
	void browseDogs(std::vector<Dog> dogs);
	void menuAdmin();
	void menuUser();
};

