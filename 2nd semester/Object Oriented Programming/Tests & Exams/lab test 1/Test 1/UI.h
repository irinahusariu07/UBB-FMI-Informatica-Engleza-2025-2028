#pragma once
#include"Repo.h"
#include"DynamicVector.h"
#include "Service.h"
#include"Protein.h"

class UI
{
private:
	Service& service;
public:
	UI(Service& s);
	int readInt(const std::string& msg);
	void printMenu();
	void run();
};

