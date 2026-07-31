#pragma once
#include"DynamicVector.h"
#include"Repository.h"
#include"Weather.h"
#include"Service.h"

class UI
{
private:
	Service& s;
public:
	UI(Service& s);
	void run();
	void printMenu();
	int readInt(const std::string& msg);
};

