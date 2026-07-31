#pragma once
#include"Repo.h"
#include"Observer.h"

class Service
{
	Repo& repo; 
	std::vector<Observer*> observers; 

public:
	Service(Repo& r) : repo{ r } {}
	std::vector<Idea> getIdeasSorted();
	std::vector<Idea> getAcceptedSorted(); 

	void registerObs(Observer* o) { observers.push_back(o); }
	void notifyObs() { for (auto* o : observers) o->update(); }

	void addIdea(const std::string& desc, const std::string& creat, int act); 
	void acceptIdea(const std::string& desc, int act) { repo.acceptIdea(desc, act); notifyObs(); }
};

