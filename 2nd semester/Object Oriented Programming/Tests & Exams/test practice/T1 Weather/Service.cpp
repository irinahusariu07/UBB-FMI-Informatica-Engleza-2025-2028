#include "Service.h"
#include <stdexcept>
#include<algorithm>


Service::Service(Repository& r) : r{r}
{
}

void Service::addStation(const std::string& location, const std::string& name, const std::string& sensors)
{
	Weather s{ location, name, sensors };
	if (location == "" || name == "" || sensors == "") throw std::runtime_error("Not valid fields");
	if (r.findStation(location, name) != -1) throw std::runtime_error("Station already exists");
	r.addDB(s);
}

Weather* Service::listAll()
{
	return r.getAll();
}


DynamicVector Service::filterSensor(const std::string& sensor)
{
	Weather* all = r.getAll();
	DynamicVector containing; 
	int n = r.getSize();
	int cnt = 0; 
	for (int i = 0; i < n; i++)
	{
		if (all[i].getSensors().find(sensor) != std::string::npos)
		{
			containing.add(all[i]);
			cnt++;
		}
	}

	for (int i = 0; i < cnt - 1; i++)
	{
		for (int j = i + 1; j < cnt; j++) 
		{
			if (containing.getElem(i).getLocation() > containing.getElem(j).getLocation())
			{
				Weather aux = containing.getElem(i);
				containing.getElem(i) = containing.getElem(j);
				containing.getElem(j) = aux;
			}
		}
	}
	return containing;
}

void Service::addDefault()
{
	addStation("cj", "c", "a, ab");
	addStation("bv", "b", "a, mm");
	addStation("ny", "n", "bm");
	addStation("ld", "l", "lm, mm");
}


