#pragma once
#include "Dynamicvector.h"

class Repository
{
private:
	DynamicVector stationDataBase;
public:
	void addDB(Weather station);
	Weather* getAll();
	int getSize();
	int findStation(const std::string& location, const std::string& name);
};

