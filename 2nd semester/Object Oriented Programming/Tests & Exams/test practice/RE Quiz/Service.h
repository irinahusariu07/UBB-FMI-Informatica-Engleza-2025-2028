#pragma once
#include"Repo.h"
#include"Observer.h"

class Service
{
private:
	Repo& repo; 
	std::vector<Observer*> obs; 

public:
	Service(Repo& r) :repo{ r } {}
	std::vector<Question> getAllID();
	std::vector<Question> getAllScore();
	void notifyObs() { for (auto* o : obs) o->update(); }
	void registerObs(Observer* o) { obs.push_back(o); }
};

