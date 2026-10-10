#include "Service.h"

void Service::notifyObs()
{
	for (auto* o : obs) o->update();
}

std::vector<Recipe> Service::getAllSorted()
{
	std::vector<Recipe> result = repo.getRecipes(); 
	std::sort(result.begin(), result.end(), [&](Recipe r1, Recipe r2)
		{
			return r1.getCuisine() < r2.getCuisine();
		});
	return result; 
}

std::vector<Recipe> Service::getAllCuisine(const std::string& cuisine)
{
	std::vector<Recipe> result; 
	for (auto& r : getAllSorted())
	{
		if (r.getCuisine() == cuisine) result.push_back(r); 
	}
	return result; 
}

void Service::addRecipe(const std::string& name, const std::string& cui, int time, const std::string& ing)
{
	if (name.empty()) throw std::runtime_error("Empty name"); 
	for (auto& r : getAllSorted())
	{
		if (r.getName() == name) throw std::runtime_error("Recipe with same name exists"); 
	}

	std::vector<std::string> ingr; 
	std::string segment;
	std::stringstream si(ing);

	while (std::getline(si, segment, ','))
	{
		if (segment.empty()) continue;
		ingr.push_back(segment);
	}

	Recipe r{ name, cui, time, ingr };
	repo.addRecipe(r); 
	notifyObs();
}

std::vector<Recipe> Service::filterIngredients(const std::string& ing)
{
	std::vector<Recipe> result; 

	//make ingredient vector from string 
	std::vector<std::string> ingr;
	std::string segment;
	std::stringstream si(ing);

	while (std::getline(si, segment, ','))
	{
		if (segment.empty()) continue;
		ingr.push_back(segment);
	}

	for (auto& r : getAllSorted())
	{
		bool all = true;
		for (int i = 0; i < ingr.size(); i++)
		{
			bool found = false;
			for (int j = 0; j < r.getIngredients().size(); j++)
			{
				if (r.getIngredients()[j] == ingr[i]) found = true;
			}
			if (!found) all = false;
		}
		if (all) result.push_back(r);
	}
	return result;

}


