#pragma once
#include"Chef.h"
#include"Recipe.h"
#include<sstream>
#include<fstream>

class Repo
{
private:
	std::string cfile, rfile; 
	std::vector<Recipe> recipes; 
	std::vector<Chef> chefs; 

public:
	Repo(const std::string& ch, const std::string& re) : cfile{ ch }, rfile{ re } {
		readChefFile(); 
		readRecipeFile();
	}

	void readChefFile(); 
	void readRecipeFile(); 
	void writeRecipeFile(); 

	std::vector<Chef>& getChefs() { return chefs; }
	std::vector<Recipe>& getRecipes() { return recipes; }

	void addRecipe(Recipe r);
};

