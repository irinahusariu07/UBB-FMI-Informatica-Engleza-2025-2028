#pragma once
#include "Person.h"

class UI
{
private:
	Person& p; 
public:
	UI(Person& p) : p{ p } {}
	void printMenu(); 
	void run(); 
};

