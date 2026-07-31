#pragma once
#include"Car.h"
#include"DynamicVector.h"
#include"Repo.h"
#include"Service.h"
#include<iostream>

class UI
{
private:
	Service& service; 
public:
	UI(Service& service);
	void printMenu();
	void run();
	std::string toLower(const std::string& txt);
	std::string strip(const std::string& txt);
	int readInt(const std::string& msg);
};



