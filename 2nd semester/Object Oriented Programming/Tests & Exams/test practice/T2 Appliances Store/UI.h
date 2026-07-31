#pragma once
#include"Service.h"
#include"Refrigerator.h"
#include"DishWasher.h"
#include <string>


class UI
{
private:
	Service& s; 
public:
	UI(Service& s) : s{ s } {}
	void printMenu(); 
	void run(); 
};

