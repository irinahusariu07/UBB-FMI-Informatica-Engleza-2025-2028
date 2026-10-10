#pragma once
#include "County.h"
#include <iostream>
#include <string>

class Party : public County
{
private:
	std::string name; 
	int votes; 

public:
	Party(const std::string& county, const std::string& name, int votes) : County(county), name{ name }, votes{ votes } {}
	bool eligible() override; 
	int mandates() override; 
	std::string toString() override; 

};

