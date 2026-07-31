#pragma once
#include"Repo.h"
#include<cmath>
#include "Observer.h"

class Service
{
	Repo& repo; 
	std::vector<Observer*> observers;
public:
	Service(Repo& r) : repo{ r } {};
	std::vector<Report> getReports() { return repo.getReports(); }
	void addReport(const std::string& desc, const std::string& reporter, int lat, int longi, int status); 
	int getDistance(int lat1, int long1, int lat2, int long2) { return sqrt((lat2 - lat1) * (lat2 - lat1) + (long2 - long1) * (long2 - long1)); }
	std::vector<Report> getAllInRadius(const std::string& name); 
	void validateReport(const std::string& desc, int lat, int longi, const std::string& validator);
	void registerOserver(Observer* o) { observers.push_back(o); }
	void notifyObserver() { for (auto o : observers)  o->update(); }
	std::vector<Driver> getDrivers() const { return repo.getDrivers(); }
};

