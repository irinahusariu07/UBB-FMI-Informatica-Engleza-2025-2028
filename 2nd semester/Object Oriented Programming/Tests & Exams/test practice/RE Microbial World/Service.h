#pragma once
#include"Repo.h"
#include"Observer.h"

class Service
{
	std::vector<Observer*> observers; 
	Repo& repo; 

public:
	Service(Repo& r) :repo{ r } {}
	std::vector<Bacteria>& getBacteria();
	
	void notifyObs() { for (auto* o : observers) o->update(); }
	void registerObs(Observer* o) { observers.push_back(o); }

	std::vector<Bacteria> getBacteriaForBiologist(std::vector<std::string> list);
	std::vector<Bacteria> filterSpecies(const std::string& spec);
	void addBacteria(const std::string& name, const std::string& species, int size, const std::string& dis); 
	std::vector<std::string>getDiseases(const std::string& name, const std::string& spec); 
	void addDisease(const std::string& name, const std::string& spec, const std::string& disease) { repo.addDisease(name, spec, disease); notifyObs(); }
};

