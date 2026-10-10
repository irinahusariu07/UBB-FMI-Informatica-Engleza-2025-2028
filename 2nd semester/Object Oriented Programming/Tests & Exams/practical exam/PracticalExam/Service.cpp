#include "Service.h"

void Service::addParcel(const std::string& rec, const std::string& street, int number, int x, int y)
{
	for (auto& p : repo.getParcels())
	{
		if (p.getRecipient() == rec) throw std::runtime_error("Parcel already exists!");
	}

	Parcel p{ rec, street, number, x, y, false };
	repo.addParcel(p);
	notifyObservers();
}

std::vector<Parcel> Service::getParcelsForDriver(const std::string& name)
{
	std::vector<Parcel> result;
	for (auto& a : getAgents())
	{
		if (a.getName() == name)
		{
			for (auto& p : getParcels())
			{
				if ((a.getStreets().find(p.getStreet()) != std::string::npos || this->inRadius(p.getLocX(), p.getLocY(), a.getCircleX(), a.getCircleY(), a.getRad())) && p.getStatus() == false)
				{
					result.push_back(p);
				}
			}
		}
	}
	return result; 
}

bool Service::inRadius(int locX, int locY, int aX, int aY, int radius)
{
	int dx = aX - locX; 
	int dy = aY - locY; 
	return (dx * dx + dy * dy) <= radius * radius;
}

void Service::deliverParcel(const std::string& rec)
{
	repo.updateParcel(rec);
	notifyObservers();
}
