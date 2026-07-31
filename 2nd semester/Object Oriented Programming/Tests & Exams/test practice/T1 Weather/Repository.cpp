#include "Repository.h"

void Repository::addDB(Weather station)
{
	stationDataBase.add(station);
}

Weather* Repository::getAll()
{
	return stationDataBase.getAll();
}

int Repository::getSize()
{
	return stationDataBase.getSize();
}

int Repository::findStation(const std::string& location, const std::string& name)
{
	Weather* stations = getAll();
	int n = getSize();
	for (int i = 0; i < n; i++)
	{
		if (stations[i].getLocation() == location && stations[i].getName() == name)
		{
			return i; 
		}
	}
	return -1; 
}




