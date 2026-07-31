#include "Service.h"

void Service::addStar(const std::string& name, const std::string& constell, int ra, int dec, int diam)
{
	if (name == "" || diam <= 0) throw std::runtime_error("Not valid star!");
	for (auto& s : getStars())
	{
		if (s.getName() == name)
			throw std::runtime_error("Star with name already exists!");
	}
	Star s{ name, constell, ra, dec, diam };
	repo.addStar(s);
	notifyOserver();
}

std::vector<Star> Service::filterByConstellation(const std::string& constell)
{
	std::vector<Star> all = getStars();
	std::vector<Star> result;
	for (auto& s : all)
	{
		if (s.getConstellation() == constell)
		{
			result.push_back(s);
		}
	}
	return result;
}

std::vector<Star> Service::getByName(const std::string& txt)
{
	std::vector<Star> all = getStars();
	std::vector<Star> result;
	for (auto& s : all)
	{
		if (s.getName().find(txt) != std::string::npos)
		{
			result.push_back(s);
		}
	}
	return result;
}





