#pragma once
#include "Appliance.h"
class Refrigerator : public Appliance
{
private:
	std::string privateUsageClass;
	bool hasFreezer;

public:
	Refrigerator(const std::string& id, const std::string& privateUsageClass, bool hasFreezer) : Appliance(id), privateUsageClass{ privateUsageClass }, hasFreezer{ hasFreezer } {}
	std::string getUsageClass() {return privateUsageClass;}
	double consumeElectricity() override; 
	std::string toString() override; 

};

