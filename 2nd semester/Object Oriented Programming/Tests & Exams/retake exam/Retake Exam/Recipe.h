#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Recipe
{
	std::string name, cuisine; 
	std::vector<std::string> ingredients; 
	int time; 

public:
	Recipe(const std::string& na, const std::string& cui, int ti, std::vector<std::string> ing) :
		name{ na }, cuisine{ cui }, time{ ti }, ingredients{ ing } {
	}

	std::string getName() const { return name; }
	std::string getCuisine() const { return cuisine; }
	int getTime() const { return time; }
	std::vector<std::string> getIngredients() { return ingredients; }

	std::string formatIng();
};