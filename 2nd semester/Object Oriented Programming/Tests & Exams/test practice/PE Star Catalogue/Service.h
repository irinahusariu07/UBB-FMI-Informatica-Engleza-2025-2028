#pragma once
#include"Repo.h"
#include"Observer.h"

class Service 
{
	Repo& repo;
	std::vector<Observer*> observers; 

public:
	Service(Repo& r) : repo { r } {}
	void addStar(const std::string& name, const std::string& constell, int ra, int dec, int diam);
	std::vector<Star> getStars() const { return repo.getStars(); }
	std::vector<Star> filterByConstellation(const std::string& constell);
	std::vector<Star> getByName(const std::string& txt);
	void registerObserver(Observer* o) { observers.push_back(o); }
	void notifyOserver() { for (auto o : observers) o->update(); }

};

