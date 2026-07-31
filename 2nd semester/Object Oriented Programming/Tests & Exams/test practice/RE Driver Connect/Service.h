#pragma once
#include"Repo.h"
#include"Observer.h"
class Service
{
private:
	Repo& repo; 
	std::vector<Observer*> obs; 

public:
	Service(Repo& r) : repo{ r } {}

	std::vector<Report> getAllInRadius(int dla, int dlo, int rad);
	int computeDistance(int la1, int lo1, int la2, int lo2) { return sqrt((la1 - la2) * (la1 - la2) + (lo1 - lo2) * (lo1 - lo2)); }
	void addReport(const std::string& desc, const std::string& reporter, int lat, int lon, int dla, int dlo);
	void validateReport(const std::string& desc, int lat, int lon, const std::string& name);
	std::vector<Driver>& getDrivers() { return repo.getDrivers(); }

	void registerObs(Observer* o) { obs.push_back(o); }
	void notifyObs() { for (auto* o : obs) o->update(); }
};

