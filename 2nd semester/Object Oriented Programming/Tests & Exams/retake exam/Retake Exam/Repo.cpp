#include "Repo.h"

void Repo::readChefFile()
{
	std::ifstream file(cfile); 
	if (!file.is_open()) throw std::runtime_error("Chef file corrupted"); 

	std::string line; 
	chefs.clear(); 

	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		
		std::stringstream ss(line); 
		std::string name, cui; 

		std::getline(ss, name, '|');
		std::getline(ss, cui, '|');

		Chef c{ name, cui }; 
		chefs.push_back(c); 
	}
	file.close();
}

void Repo::readRecipeFile()
{
	std::ifstream file(rfile); 
	if (!file.is_open()) throw std::runtime_error("Recipe file corrupted"); 

	std::string line; 
	recipes.clear(); 

	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string name, cui, time, ingr; 

		std::getline(ss, name, '|'); 
		std::getline(ss, cui, '|'); 
		std::getline(ss, time, '|'); 
		std::getline(ss, ingr, '|'); 

		std::string segment; 
		std::stringstream si(ingr); 
		std::vector<std::string> ingredients; 

		while (std::getline(si, segment, ','))
		{
			if (segment.empty()) continue; 
			ingredients.push_back(segment); 
		}

		Recipe r{ name, cui, std::stoi(time), ingredients }; 
		recipes.push_back(r); 
	}
	file.close();
}

void Repo::writeRecipeFile()
{
	std::ofstream file(rfile);
	if (!file.is_open()) throw std::runtime_error("Recipe file writing problem");

	std::vector<Recipe> result = recipes;
	std::sort(result.begin(), result.end(), [&](Recipe r1, Recipe r2)
		{
			return (r1.getCuisine() < r2.getCuisine() && r1.getTime() < r2.getTime());
		});

	for (auto& r : result)
	{
		file << r.getName() << "|" << r.getCuisine() << "|" << r.getTime() << "|"; 
		std::vector<std::string> ingredients = r.getIngredients();
		for (int i = 0; i < ingredients.size(); i++)
		{
			file << ingredients[i]; 
			if (i < ingredients.size() - 1) file << ',';
		}
		file << "\n";
	}
	file.close(); 
}

void Repo::addRecipe(Recipe r)
{
	recipes.push_back(r); 
	writeRecipeFile(); 
}


