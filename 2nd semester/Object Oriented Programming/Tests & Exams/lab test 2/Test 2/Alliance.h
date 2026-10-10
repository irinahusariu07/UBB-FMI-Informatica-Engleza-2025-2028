#pragma once
#include "County.h"
class Alliance : public County
{
private:
	std::string name; 
	int votes; 
	int number; 

public:
	Alliance(const std::string& county, const std::string& name, int votes, int number) : County(county), name{ name }, votes{ votes }, number{ number } {}
	bool eligible() override;
	int mandates() override;
	std::string toString() override;
};

