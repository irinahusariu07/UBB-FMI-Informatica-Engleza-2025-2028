#pragma once
#include "DynamicVector.h"
#include "Weather.h"
#include "Repository.h"

class Service
{
private:
	Repository& r; 
public:
	Service(Repository& r);
	void addStation(const std::string& location, const std::string& name, const std::string& sensors);
	Weather* listAll(); 
	DynamicVector filterSensor(const std::string& sensor);
	void addDefault();
	int getSize() { return r.getSize(); }
};

