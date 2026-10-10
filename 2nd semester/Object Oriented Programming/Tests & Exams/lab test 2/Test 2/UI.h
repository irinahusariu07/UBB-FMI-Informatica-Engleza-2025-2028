#pragma once
#include"Service.h"
class UI
{
private:
	Service& s;
public:
	UI(Service& s) : s{ s } {}
	void run(); 

};

