#pragma once
#include "Appliance.h"
#include<fstream>

class Service
{
private:
	std::vector<Appliance*> appliances; 

public:
	void addAppliance(Appliance* a) { appliances.push_back(a); }
	std::vector<Appliance*> getAllAppliances() { return appliances; }
	std::vector<Appliance*> getAllWithCEnergyLessThan(double maxE);
	void writeToFile(const std::string& filename, double maxE); 
};

