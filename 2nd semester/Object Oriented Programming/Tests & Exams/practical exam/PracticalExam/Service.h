#pragma once
#include"Repo.h"
#include"Observer.h"

class Service
{
	Repo& repo; 
	std::vector<Observer*> observers;

public:
	Service(Repo& r) : repo{ r } {}
	std::vector<Agent> getAgents() { return repo.getAgents(); }
	std::vector<Parcel> getParcels() { return repo.getParcels(); }
	void addParcel(const std::string& rec, const std::string& street, int number, int x, int y);
	std::vector<Parcel> getParcelsForDriver(const std::string& name);
	bool inRadius(int locX, int locY, int aX, int aY, int radius);
	void deliverParcel(const std::string& rec);
	void registerObserver(Observer* o) { observers.push_back(o); }
	void notifyObservers() {for (auto o : observers) o->update();}



};


