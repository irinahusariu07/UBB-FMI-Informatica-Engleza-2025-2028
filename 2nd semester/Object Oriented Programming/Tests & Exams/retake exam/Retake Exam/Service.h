#pragma once
#include"Observer.h"
#include"Repo.h"

class Service
{
private:
	Repo& repo; 
	std::vector<Observer*> obs; 

public:
	Service(Repo& r) : repo{ r } {}

	void registerObs(Observer* o) { obs.push_back(o); }
	void notifyObs();

	std::vector<Recipe> getAllSorted();
	std::vector<Chef> getChefs() { return repo.getChefs(); }

	std::vector<Recipe> getAllCuisine(const std::string& cuisine); 

	void addRecipe(const std::string& name, const std::string& cui, int time, const std::string& ing);
	std::vector<Recipe> filterIngredients(const std::string& ing);
};

